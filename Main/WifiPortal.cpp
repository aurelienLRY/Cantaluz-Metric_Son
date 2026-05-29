/*
 * WifiPortal.cpp — SoftAP ESP8266 + interface mobile Cantaluz
 */

#include "WifiPortal.h"
#include "Config.h"

#if WIFI_ENABLE

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "AppState.h"
#include "LedStrip.h"

static ESP8266WebServer server(WIFI_HTTP_PORT);
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

static const char PAGE_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Cantaluz</title>
<style>
*{box-sizing:border-box}
body{font-family:system-ui,sans-serif;margin:0;padding:1rem;background:#0d1a12;color:#e8f5e9}
h1{font-size:1.4rem;margin:0 0 .25rem;color:#7cff9a}
.sub{opacity:.75;font-size:.85rem;margin-bottom:1rem}
.card{background:#152820;border-radius:12px;padding:1rem;margin-bottom:1rem}
.row{display:flex;justify-content:space-between;margin:.35rem 0}
.val{font-weight:700;color:#7cff9a}
label{display:block;margin:.75rem 0 .25rem;font-size:.9rem}
input[type=range]{width:100%}
button{width:100%;margin-top:1rem;padding:.75rem;border:0;border-radius:8px;
background:#2e7d32;color:#fff;font-size:1rem;font-weight:600}
.state{font-size:1.2rem;text-align:center;padding:.5rem}
</style>
</head>
<body>
<h1>Cantaluz</h1>
<p class="sub">La lumière qui répond au son — réglages live</p>
<div class="card">
<div class="state" id="state">—</div>
<div class="row"><span>Peak micro</span><span class="val" id="peak">0</span></div>
<div class="row"><span>Barre VU</span><span class="val" id="bar">0 %</span></div>
<div class="row"><span>Calibration max</span><span class="val" id="vuMax">0</span></div>
</div>
<div class="card">
<label>Zone verte (peak ≤) <span id="vVert"></span></label>
<input type="range" id="vert" min="50" max="900" step="10">
<label>Zone orange (peak ≤) <span id="vOrange"></span></label>
<input type="range" id="orange" min="100" max="1020" step="10">
<label>Luminosité <span id="vBright"></span></label>
<input type="range" id="bright" min="5" max="255" step="5">
<label>Montée barre (%) <span id="vAttack"></span></label>
<input type="range" id="attack" min="5" max="100" step="5">
<button type="button" id="apply">Appliquer</button>
</div>
<p class="sub">IP : <span id="ip">192.168.4.1</span></p>
<script>
function qs(id){return document.getElementById(id)}
function syncSliders(j){
  qs('vert').value=j.vert; qs('orange').value=j.orange;
  qs('bright').value=j.brightness; qs('attack').value=j.attack;
  qs('vVert').textContent=j.vert;
  qs('vOrange').textContent=j.orange;
  qs('vBright').textContent=j.brightness;
  qs('vAttack').textContent=j.attack;
}
async function refresh(){
  try{
    const r=await fetch('/api/status');
    const j=await r.json();
    qs('state').textContent=j.state;
    qs('peak').textContent=j.peak;
    qs('bar').textContent=Math.round(j.display*100)+' %';
    qs('vuMax').textContent=j.vuMax;
    if(!window._slidersInit){syncSliders(j);window._slidersInit=1}
    qs('ip').textContent=j.ip;
  }catch(e){}
}
['vert','orange','bright','attack'].forEach(function(id){
  qs(id).oninput=function(){
    if(id==='vert') qs('vVert').textContent=this.value;
    else if(id==='orange') qs('vOrange').textContent=this.value;
    else if(id==='bright') qs('vBright').textContent=this.value;
    else qs('vAttack').textContent=this.value;
  };
});
qs('apply').onclick=async function(){
  const p=new URLSearchParams({
    vert:qs('vert').value, orange:qs('orange').value,
    bright:qs('bright').value, attack:qs('attack').value
  });
  await fetch('/api/settings?'+p.toString());
  refresh();
};
setInterval(refresh,450);
refresh();
</script>
</body>
</html>
)rawliteral";

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
  ledComputeZonesFromPlages();
}

static void handleRoot() {
  server.send_P(200, PSTR("text/html"), PAGE_HTML);
}

static void handleStatus() {
  IPAddress ip = WiFi.softAPIP();
  char buf[360];
  int displayPct = (int)(g.displayLevel * 100.0f + 0.5f);
  snprintf(buf, sizeof(buf),
    "{\"peak\":%d,\"avg\":%d,\"display\":%.3f,\"displayPct\":%d,"
    "\"state\":\"%s\",\"vuMax\":%d,"
    "\"vert\":%d,\"orange\":%d,\"brightness\":%u,\"attack\":%u,"
    "\"ip\":\"%u.%u.%u.%u\",\"ssid\":\"%s\"}",
    g.lastPeak,
    g.lastMicAvg,
    g.displayLevel,
    displayPct,
    stateName(g.currentState),
    g.vuMaxPeak,
    g.live.adcFinZoneVert,
    g.live.adcFinZoneOrange,
    (unsigned)g.live.maxBrightness,
    (unsigned)g.live.attackPercent,
    ip[0], ip[1], ip[2], ip[3],
    WIFI_AP_SSID);
  server.send(200, F("application/json"), buf);
}

static void handleSettings() {
  wifiApplySettingsFromRequest();
  server.send(200, F("application/json"), F("{\"ok\":true}"));
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
  server.on("/", handleRoot);
  server.on("/api/status", handleStatus);
  server.on("/api/settings", handleSettings);
  server.begin();
  s_webRunning = true;
  wifiLogHeap(F("Serveur HTTP"));
}

void wifiPortalSetup() {
  wifiPortalStartRadio();
  wifiPortalStartWeb();
}

void wifiPortalLoop() {
  WiFi.setSleepMode(WIFI_NONE_SLEEP);

  if (s_webRunning) {
    server.handleClient();
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
