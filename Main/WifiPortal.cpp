/*
 * WifiPortal.cpp — SoftAP ESP8266 + interface mobile Cantaluz
 */

#include "WifiPortal.h"
#include "Config.h"

#if WIFI_ENABLE

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>

#include "AppState.h"
#include "LedStrip.h"
#include "Modes.h"
#include "ModeMeditation.h"
#include "MicSensor.h"
#include "WebAppHtml.h"

static ESP8266WebServer server(WIFI_HTTP_PORT);
static DNSServer dnsServer;
static const byte WIFI_DNS_PORT = 53;
static bool s_mdnsRunning = false;
static bool s_dnsRunning = false;
static bool s_apRunning = false;
static bool s_webRunning = false;
static unsigned long s_lastApCheckMs = 0;
static unsigned long s_lastHeartbeatMs = 0;
static unsigned long s_lastLedToggleMs = 0;
static bool s_ledApState = false;

// LED bleue WeMos (GPIO2) : allumée = Wi-Fi AP actif (pas de LED Wi-Fi dédiée sur D1 R1)
static void wifiLedApOk(bool on) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, on ? LOW : HIGH);
  s_ledApState = on;
}

static void wifiPrintIp(const IPAddress &ip) {
  Serial.print(ip[0]);
  Serial.print('.');
  Serial.print(ip[1]);
  Serial.print('.');
  Serial.print(ip[2]);
  Serial.print('.');
  Serial.println(ip[3]);
}

static void wifiLogHeap(const __FlashStringHelper *label) {
  Serial.print(label);
  Serial.print(F(" heap="));
  Serial.print(ESP.getFreeHeap());
  Serial.print(F(" bloc="));
  Serial.println(ESP.getMaxFreeBlockSize());
}

static void wifiApplyToHardware() {
  FastLED.setBrightness(g.live.maxBrightness);
  ledComputeZonesFromPlages();
}

static void wifiApplySettingsFromRequest() {
  if (server.hasArg("vert")) {
    int v = server.arg("vert").toInt();
    if (v >= 0 && v <= 1022) {
      g.live.adcFinZoneVert = v;
    }
  }
  if (server.hasArg("orange")) {
    int v = server.arg("orange").toInt();
    if (v >= 1 && v <= 1023) {
      g.live.adcFinZoneOrange = v;
    }
  }
  if (g.live.adcFinZoneOrange <= g.live.adcFinZoneVert) {
    g.live.adcFinZoneOrange = g.live.adcFinZoneVert + 1;
  }
  if (server.hasArg("bright")) {
    int v = server.arg("bright").toInt();
    if (v >= 0 && v <= 255) {
      g.live.maxBrightness = (uint8_t)v;
      FastLED.setBrightness(g.live.maxBrightness);
    }
  }
  if (server.hasArg("attack")) {
    int v = server.arg("attack").toInt();
    if (v >= 0 && v <= 100) {
      g.live.attackPercent = (uint8_t)v;
      liveApplyAttackRate();
    }
  }
  if (server.hasArg("sens") || server.hasArg("sensitivity")) {
    int v = server.hasArg("sens")
      ? server.arg("sens").toInt()
      : server.arg("sensitivity").toInt();
    if (v >= 0 && v <= 100) {
      g.live.sensitivity = (uint8_t)v;
      micApplySensitivity();
    }
  }
  if (server.hasArg("mode")) {
    int m = server.arg("mode").toInt();
    if (m == MODE_IMMEDIAT || m == MODE_LENT || m == MODE_MEDITATION) {
      modesSetActive((uint8_t)m);
    }
  }
  wifiApplyToHardware();
}

static const char *wifiModeLabel(uint8_t mode) {
  if (mode == MODE_LENT) return "Standard";
  if (mode == MODE_MEDITATION) return "Méditation guidée";
  return "Flash";
}

static const char *wifiStateLabel(ColorState s) {
  switch (s) {
    case STATE_GREEN:  return "Calme";
    case STATE_ORANGE: return "Animé";
    case STATE_RED:    return "Intense";
  }
  return "Calme";
}

static void handleReset() {
  if (server.hasArg(F("field"))) {
    String f = server.arg(F("field"));
    f.toLowerCase();
    liveResetField(f.c_str());
    wifiApplyToHardware();
    char buf[200];
    snprintf(buf, sizeof(buf),
      "{\"ok\":true,\"field\":\"%s\",\"vert\":%d,\"orange\":%d,\"brightness\":%u,\"attack\":%u,\"sensitivity\":%u}",
      f.c_str(),
      g.live.adcFinZoneVert,
      g.live.adcFinZoneOrange,
      (unsigned)g.live.maxBrightness,
      (unsigned)g.live.attackPercent,
      (unsigned)g.live.sensitivity);
    server.send(200, F("application/json"), buf);
    return;
  }

  uint8_t mode = g.live.activeMode;
  liveConfigResetDefaults();
  modesSetActive(mode);
  wifiApplyToHardware();
  server.send(200, F("application/json"), F("{\"ok\":true,\"reset\":\"all\"}"));
}

static void wifiSendNoCacheHeaders() {
  server.sendHeader(F("Cache-Control"), F("no-cache, no-store, must-revalidate"));
  server.sendHeader(F("Pragma"), F("no-cache"));
  server.sendHeader(F("Expires"), F("0"));
  server.sendHeader(F("Connection"), F("close"));
}

static void handleApp() {
  wifiSendNoCacheHeaders();
  server.send_P(200, PSTR("text/html"), APP_HTML);
}

static void handleCaptiveLanding() {
  handleApp();
}

static void handleCaptiveHead() {
  wifiSendNoCacheHeaders();
  server.send(200, F("text/html"), F(""));
}

static void handleNotFound() {
  if (server.method() == HTTP_HEAD) {
    handleCaptiveHead();
    return;
  }
  if (server.method() == HTTP_GET) {
    handleCaptiveLanding();
    return;
  }
  server.send(404, F("text/plain"), F("Not found"));
}

static void wifiRegisterCaptiveRoutes() {
  server.on("/generate_204", handleCaptiveLanding);
  server.on("/gen_204", handleCaptiveLanding);
  server.on("/mobile/status.php", handleCaptiveLanding);
  server.on("/canonical.html", handleCaptiveLanding);
  server.on("/success.txt", handleCaptiveLanding);
  server.on("/success.html", handleCaptiveLanding);
  server.on("/chat", handleCaptiveLanding);
  server.on("/hotspot-detect.html", handleCaptiveLanding);
  server.on("/library/test/success.html", handleCaptiveLanding);
  server.on("/connecttest.txt", handleCaptiveLanding);
  server.on("/ncsi.txt", handleCaptiveLanding);
  server.on("/redirect", handleCaptiveLanding);
  server.on("/fwlink", handleCaptiveLanding);
  server.on("/check_network_status.txt", handleCaptiveLanding);
}

static void wifiPortalStartDnsMdns() {
#if WIFI_CAPTIVE_PORTAL
  dnsServer.stop();
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  if (dnsServer.start(WIFI_DNS_PORT, "*", WiFi.softAPIP())) {
    s_dnsRunning = true;
  } else {
    s_dnsRunning = false;
    Serial.println(F("DNS portail: ECHEC"));
  }
#else
  s_dnsRunning = false;
#endif

  MDNS.end();
  s_mdnsRunning = false;
  if (MDNS.begin(WIFI_MDNS_NAME)) {
    MDNS.addService("http", "tcp", WIFI_HTTP_PORT);
    s_mdnsRunning = true;
    Serial.print(F("Adresse locale: http://"));
    Serial.print(WIFI_MDNS_NAME);
    Serial.println(F(".local"));
  } else {
    Serial.println(F("mDNS: ECHEC (utiliser http://192.168.4.1)"));
  }
}

static void handleMeditationStart() {
  if (g.live.activeMode != MODE_MEDITATION) {
    server.send(400, F("application/json"), F("{\"ok\":false,\"err\":\"mode\"}"));
    return;
  }
  uint16_t dur = MEDIT_DUR_5MIN_SEC;
  if (server.hasArg("dur")) {
    dur = (uint16_t)server.arg("dur").toInt();
  }
  if (dur != MEDIT_DUR_2MIN_SEC && dur != MEDIT_DUR_5MIN_SEC && dur != MEDIT_DUR_10MIN_SEC) {
    dur = MEDIT_DUR_5MIN_SEC;
  }
  meditationStart(dur);
  char buf[128];
  snprintf(buf, sizeof(buf),
    "{\"ok\":true,\"dur\":%u,\"countdown\":%u}",
    (unsigned)dur, (unsigned)MEDIT_COUNTDOWN_SEC);
  server.send(200, F("application/json"), buf);
}

static void handleMeditationStop() {
  meditationStop();
  server.send(200, F("application/json"), F("{\"ok\":true}"));
}

static void handleStatus() {
  IPAddress ip = WiFi.softAPIP();
  char buf[780];
  int displayPct = (int)(g.displayLevel * 100.0f + 0.5f);
  snprintf(buf, sizeof(buf),
    "{\"niveau\":%d,\"barre\":%d,\"display\":%.3f,"
    "\"couleur\":\"%s\","
    "\"vert\":%d,\"orange\":%d,\"brightness\":%u,\"attack\":%u,\"sensitivity\":%u,"
    "\"defVert\":%d,\"defOrange\":%d,\"defBright\":%u,\"defAttack\":%u,\"defSens\":%u,"
    "\"mode\":%u,\"modeName\":\"%s\","
    "\"medPhase\":\"%s\",\"medCountdown\":%u,\"medElapsed\":%lu,\"medRemain\":%lu,"
    "\"medDur\":%lu,\"medRunning\":%s,\"medCounting\":%s,"
    "\"ip\":\"%u.%u.%u.%u\",\"host\":\"%s.local\",\"ssid\":\"%s\"}",
    displayPct,
    displayPct,
    g.displayLevel,
    wifiStateLabel(g.currentState),
    g.live.adcFinZoneVert,
    g.live.adcFinZoneOrange,
    (unsigned)g.live.maxBrightness,
    (unsigned)g.live.attackPercent,
    (unsigned)g.live.sensitivity,
    ADC_FIN_ZONE_VERT,
    ADC_FIN_ZONE_ORANGE,
    (unsigned)(g.live.activeMode == MODE_LENT ? LENT_MAX_BRIGHTNESS : MAX_BRIGHTNESS),
    (unsigned)(g.live.activeMode == MODE_LENT ? LENT_ATTACK_PERCENT : ATTACK_PERCENT),
    (unsigned)DEFAULT_SENSITIVITY,
    (unsigned)g.live.activeMode,
    wifiModeLabel(g.live.activeMode),
    meditationPhaseLabel(g.med.phase),
    (unsigned)meditationCountdownRemainSec(),
    (unsigned long)meditationSessionElapsedSec(),
    (unsigned long)meditationSessionRemainSec(),
    (unsigned long)(g.med.sessionDurMs / 1000UL),
    g.med.sessionActive ? "true" : "false",
    g.med.countdownActive ? "true" : "false",
    ip[0], ip[1], ip[2], ip[3],
    WIFI_MDNS_NAME,
    WIFI_AP_SSID);
  server.send(200, F("application/json"), buf);
}

static void handleSettings() {
  wifiApplySettingsFromRequest();
  char buf[240];
  snprintf(buf, sizeof(buf),
    "{\"ok\":true,\"vert\":%d,\"orange\":%d,\"brightness\":%u,\"attack\":%u,\"sensitivity\":%u,\"mode\":%u}",
    g.live.adcFinZoneVert,
    g.live.adcFinZoneOrange,
    (unsigned)g.live.maxBrightness,
    (unsigned)g.live.attackPercent,
    (unsigned)g.live.sensitivity,
    (unsigned)g.live.activeMode);
  server.send(200, F("application/json"), buf);
}

static bool wifiStartSoftApOnce() {
  WiFi.persistent(false);
  WiFi.disconnect(true);
  WiFi.softAPdisconnect(true);
  delay(100);

  WiFi.forceSleepWake();
  WiFi.mode(WIFI_AP);
  WiFi.enableSTA(false);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.setOutputPower(20.5f);
  WiFi.setPhyMode(WIFI_PHY_MODE_11G);

  const IPAddress apIp(192, 168, 4, 1);
  const IPAddress apGw(192, 168, 4, 1);
  const IPAddress apMask(255, 255, 255, 0);
  WiFi.softAPConfig(apIp, apGw, apMask);

  int ch = WIFI_AP_CHANNEL;
  if (ch < 1) ch = 1;
  if (ch > 13) ch = 13;

  bool ok;
  if (strlen(WIFI_AP_PASS) >= 8) {
    ok = WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASS, ch, 0, 4);
  } else {
    ok = WiFi.softAP(WIFI_AP_SSID, "", ch, 0, 4);
  }

  delay(800);
  return ok && WiFi.softAPIP()[0] != 0;
}

bool wifiPortalStartRadio() {
  wifiLogHeap(F("Avant WiFi"));
  bool ok = false;
  for (int attempt = 1; attempt <= 3; attempt++) {
    ok = wifiStartSoftApOnce();
    if (ok) break;
    Serial.print(F("  tentative SoftAP "));
    Serial.print(attempt);
    Serial.println(F(" echouee, nouvel essai..."));
    delay(500);
  }
  s_apRunning = ok;
  wifiLogHeap(F("Apres WiFi"));
  wifiLedApOk(ok);

  Serial.println();
  Serial.println(F("=== WiFi Cantaluz ==="));
  Serial.print(F("SoftAP: "));
  Serial.println(ok ? F("OK") : F("ECHEC"));
  Serial.print(F("SSID: "));
  Serial.println(WIFI_AP_SSID);
  Serial.print(F("Mot de passe: "));
  if (strlen(WIFI_AP_PASS) >= 8) {
    Serial.println(WIFI_AP_PASS);
  } else {
    Serial.println(F("(reseau ouvert)"));
  }
  Serial.print(F("Canal: "));
  Serial.println(WIFI_AP_CHANNEL);
  Serial.print(F("IP: http://"));
  wifiPrintIp(WiFi.softAPIP());
  Serial.print(F("Nom: http://"));
  Serial.print(WIFI_MDNS_NAME);
  Serial.println(F(".local"));
#if WIFI_CAPTIVE_PORTAL
  Serial.println(F("Portail captif: actif (page auto a la connexion)"));
#endif
  Serial.print(F("MAC AP: "));
  Serial.println(WiFi.softAPmacAddress());

  if (ESP.getFreeHeap() < 20000) {
    Serial.println(F("ATTENTION: peu de RAM — mettre LED_COUNT a 17 pour tester."));
  }
  if (!ok) {
    Serial.println(F(">>> Essayez le sketch WifiMinimal (dossier WifiMinimal/)"));
    for (int i = 0; i < 6; i++) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(150);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(150);
      yield();
    }
  } else {
    Serial.println(F("LED carte = allumee si Wi-Fi AP actif (GPIO2)"));
  }
  Serial.println();
  return ok;
}

void wifiPortalStartWeb() {
  if (!s_apRunning) {
    Serial.println(F("Serveur web: ignore (SoftAP inactif)"));
    return;
  }
  server.on("/", handleApp);
  server.on("/reglages", handleApp);
  server.on("/app", handleApp);
  server.on("/api/status", handleStatus);
  server.on("/api/settings", handleSettings);
  server.on("/api/reset", handleReset);
  server.on("/api/meditation/start", handleMeditationStart);
  server.on("/api/meditation/stop", handleMeditationStop);

#if WIFI_CAPTIVE_PORTAL
  wifiRegisterCaptiveRoutes();
  server.onNotFound(handleNotFound);
#endif

  server.begin();
  s_webRunning = true;
  wifiPortalStartDnsMdns();
  wifiLogHeap(F("Serveur HTTP"));
}

void wifiPortalSetup() {
  wifiPortalStartRadio();
  wifiPortalStartWeb();
}

void wifiPortalLoop() {
  WiFi.setSleepMode(WIFI_NONE_SLEEP);

#if WIFI_CAPTIVE_PORTAL
  if (s_dnsRunning) {
    for (uint8_t i = 0; i < 8; i++) {
      dnsServer.processNextRequest();
    }
  }
#endif
  if (s_mdnsRunning) {
    MDNS.update();
  }

  if (s_webRunning) {
    for (uint8_t i = 0; i < 12; i++) {
      server.handleClient();
    }
  }

  unsigned long now = millis();

  if (now - s_lastApCheckMs > 2000UL) {
    s_lastApCheckMs = now;
    IPAddress ip = WiFi.softAPIP();
    bool alive = (ip[0] != 0) && (WiFi.getMode() == WIFI_AP);
    if (!alive && s_apRunning) {
      Serial.println(F("WiFi: AP perdu en boucle — redemarrage"));
      s_apRunning = wifiStartSoftApOnce();
      wifiLedApOk(s_apRunning);
      if (s_apRunning && s_webRunning) {
        wifiPortalStartDnsMdns();
      }
    }
  }

  if (s_apRunning && now - s_lastHeartbeatMs > 10000UL) {
    s_lastHeartbeatMs = now;
    IPAddress ip = WiFi.softAPIP();
    Serial.print(F("[WiFi OK] "));
    Serial.print(WIFI_AP_SSID);
    Serial.print(F(" IP="));
    wifiPrintIp(ip);
    Serial.print(F(" stations="));
    Serial.println(WiFi.softAPgetStationNum());
  } else if (!s_apRunning && now - s_lastHeartbeatMs > 2000UL) {
    s_lastHeartbeatMs = now;
    Serial.println(F("[WiFi ECHEC] AP inactif — recherche reseau impossible"));
    if (now - s_lastLedToggleMs > 300UL) {
      s_lastLedToggleMs = now;
      digitalWrite(LED_BUILTIN, s_ledApState ? HIGH : LOW);
      s_ledApState = !s_ledApState;
    }
  }

  yield();
  delay(1);
}

#else  // !WIFI_ENABLE

bool wifiPortalStartRadio() { return false; }
void wifiPortalStartWeb() {}
void wifiPortalSetup() {}
void wifiPortalLoop() {}

#endif
