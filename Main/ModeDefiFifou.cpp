/*
 * ModeDefiFifou.cpp — Jeu du calme : gagner des LED en restant calme
 */

#include "ModeDefiFifou.h"
#include "Config.h"
#include "LedStrip.h"
#include "MicSensor.h"
#include "AppState.h"

static const CRGB FIFOU_COL = CRGB(FIFOU_COLOR_R, FIFOU_COLOR_G, FIFOU_COLOR_B);

static const CRGB FIFOU_FIREWORK_PALETTE[] = {
  CRGB(0, 200, 255),   // cyan
  CRGB(255, 0, 180),   // magenta
  CRGB(255, 200, 0),   // ambre
  CRGB(0, 255, 120),   // vert
  CRGB(255, 60, 0),    // orange
  CRGB(160, 0, 255),   // violet
};
static const uint8_t FIFOU_FIREWORK_PALETTE_COUNT =
  sizeof(FIFOU_FIREWORK_PALETTE) / sizeof(FIFOU_FIREWORK_PALETTE[0]);

static int fifouProfileIndexFromDur(uint16_t durSec) {
  if (durSec <= MEDIT_DUR_2MIN_SEC + 30) return 0;
  if (durSec <= MEDIT_DUR_5MIN_SEC + 30) return 1;
  return 2;
}

static uint16_t fifouSessionSecFromProfile(uint8_t profile) {
  switch (profile) {
    case 0: return MEDIT_DUR_2MIN_SEC;
    case 1: return MEDIT_DUR_5MIN_SEC;
    default: return MEDIT_DUR_10MIN_SEC;
  }
}

static void fifouComputeRates() {
  float ledsToGain = (float)(LED_COUNT - FIFOU_START_LEDS);
  float sessionSec = (float)(g.fifou.sessionDurMs / 1000UL);
  float calmMinSec = sessionSec * (float)FIFOU_CALM_RATIO_NUM / (float)FIFOU_CALM_RATIO_DEN;
  if (calmMinSec < 1.0f) calmMinSec = 1.0f;

  g.fifou.gainRatePerSec = ledsToGain / calmMinSec;
  g.fifou.lossRatePerSec = g.fifou.gainRatePerSec * (float)FIFOU_LOSS_GAIN_PERCENT / 100.0f;
  if (g.fifou.lossRatePerSec < 0.01f) g.fifou.lossRatePerSec = 0.01f;
}

static void fifouClearStrip() {
  fill_solid(g.leds, LED_COUNT, CRGB::Black);
  FastLED.show();
  yield();
}

static void fifouRenderStrip() {
  int lit = (int)(g.fifou.litLeds + 0.5f);
  if (lit < 0) lit = 0;
  if (lit > LED_COUNT) lit = LED_COUNT;

  for (int i = 0; i < LED_COUNT; i++) {
    g.leds[i] = (i < lit) ? FIFOU_COL : CRGB::Black;
  }
  FastLED.show();
  yield();
}

static void fifouBeginSession(unsigned long now) {
  g.fifou.countdownActive = false;
  g.fifou.sessionActive = true;
  g.fifou.endAnimActive = false;
  g.fifou.phase = FIFOU_PLAYING;
  g.fifou.sessionStartMs = now;
  g.fifou.litLeds = (float)FIFOU_START_LEDS;
  g.currentState = STATE_GREEN;
  g.peakSmooth = 0.0f;
  g.lastLoopMs = now;
  fifouComputeRates();
  fifouRenderStrip();
}

static void fifouFinishWin(unsigned long now) {
  g.fifou.sessionActive = false;
  g.fifou.endAnimActive = true;
  g.fifou.phase = FIFOU_WON;
  g.fifou.endAnimStartMs = now;
  g.fifou.litLeds = (float)LED_COUNT;
  fifouClearStrip();
}

static void fifouFinishLost(unsigned long now) {
  g.fifou.sessionActive = false;
  g.fifou.endAnimActive = true;
  g.fifou.phase = FIFOU_LOST;
  g.fifou.endAnimStartMs = now;
}

static void fifouRenderLostPulse(unsigned long now) {
  unsigned long elapsed = now - g.fifou.endAnimStartMs;
  if (elapsed >= FIFOU_LOST_PULSE_MS) {
    g.fifou.endAnimActive = false;
    g.fifou.phase = FIFOU_DONE;
    fifouClearStrip();
    return;
  }

  bool on = ((now / FIFOU_LOST_PULSE_PERIOD_MS) & 1) == 0;
  fill_solid(g.leds, LED_COUNT, on ? CRGB::Red : CRGB::Black);
  FastLED.show();
  yield();
}

static void fifouRenderFireworks(unsigned long now) {
  unsigned long elapsed = now - g.fifou.endAnimStartMs;
  if (elapsed >= FIFOU_WIN_FIREWORKS_MS) {
    g.fifou.endAnimActive = false;
    g.fifou.phase = FIFOU_DONE;
    fifouClearStrip();
    return;
  }

  for (int i = 0; i < LED_COUNT; i++) {
    g.leds[i].nscale8_video(205);
  }

  const unsigned long burstPeriod = 380UL;
  unsigned long burstIdx = elapsed / burstPeriod;
  unsigned long phaseInBurst = elapsed % burstPeriod;
  int center = (int)(((burstIdx * 67UL + 31UL) * (unsigned long)LED_COUNT) / 97UL);
  if (center >= LED_COUNT) center %= LED_COUNT;
  CRGB col = FIFOU_FIREWORK_PALETTE[burstIdx % FIFOU_FIREWORK_PALETTE_COUNT];

  int maxR = 5 + (int)(phaseInBurst / 32UL);
  if (maxR > 30) maxR = 30;

  for (int d = 0; d <= maxR; d++) {
    uint8_t fade = 255 - (uint8_t)((d * 230) / (maxR + 1));
    CRGB c = col;
    c.nscale8_video(fade);
    int li = center - d;
    int ri = center + d;
    if (li >= 0 && li < LED_COUNT) g.leds[li] = c;
    if (ri >= 0 && ri < LED_COUNT && ri != li) g.leds[ri] = c;
  }

  FastLED.show();
  yield();
}

static void fifouRenderCountdown(unsigned long now) {
  unsigned long elapsed = now - g.fifou.countdownStartMs;
  unsigned long totalMs = (unsigned long)FIFOU_COUNTDOWN_SEC * 1000UL;
  if (elapsed >= totalMs) return;

  float progress = (float)elapsed / (float)totalMs;
  uint16_t span = FIFOU_COUNTDOWN_BLINK_MAX_MS - FIFOU_COUNTDOWN_BLINK_MIN_MS;
  uint16_t period = FIFOU_COUNTDOWN_BLINK_MAX_MS - (uint16_t)(progress * span);
  if (period < FIFOU_COUNTDOWN_BLINK_MIN_MS) period = FIFOU_COUNTDOWN_BLINK_MIN_MS;

  bool on = ((now / period) & 1) == 0;
  fill_solid(g.leds, LED_COUNT, on ? FIFOU_COL : CRGB::Black);
  FastLED.show();
  yield();
}

const char *defiFifouPhaseLabel(FifouPhase phase) {
  switch (phase) {
    case FIFOU_IDLE:      return "idle";
    case FIFOU_COUNTDOWN: return "countdown";
    case FIFOU_PLAYING:   return "playing";
    case FIFOU_WON:       return "won";
    case FIFOU_LOST:      return "lost";
    case FIFOU_DONE:      return "done";
  }
  return "idle";
}

void defiFifouStop() {
  g.fifou.sessionActive = false;
  g.fifou.countdownActive = false;
  g.fifou.endAnimActive = false;
  g.fifou.phase = FIFOU_IDLE;
  fifouClearStrip();
}

bool defiFifouStart(uint16_t durSec) {
  g.fifou.durProfile = fifouProfileIndexFromDur(durSec);
  g.fifou.sessionDurMs = (uint32_t)fifouSessionSecFromProfile(g.fifou.durProfile) * 1000UL;
  g.fifou.sessionActive = false;
  g.fifou.countdownActive = true;
  g.fifou.endAnimActive = false;
  g.fifou.phase = FIFOU_COUNTDOWN;
  g.fifou.countdownStartMs = millis();
  g.fifou.litLeds = (float)FIFOU_START_LEDS;
  fifouClearStrip();
  return true;
}

void modeDefiFifouSetup() {
  defiFifouStop();
  g.fifou.durProfile = 0;
  g.fifou.sessionDurMs = (uint32_t)MEDIT_DUR_2MIN_SEC * 1000UL;
  ledComputeZonesFromPlages();
  ledInitHardware();
  configApply();
  FastLED.setBrightness(g.live.maxBrightness);
  micInitVuFromSettings();
  g.lastLoopMs = millis();
  fifouClearStrip();
}

void modeDefiFifouLoop() {
  static unsigned long s_lastFrameMs = 0;
  unsigned long now = millis();

  if (g.fifou.endAnimActive) {
    if (g.fifou.phase == FIFOU_LOST) {
      fifouRenderLostPulse(now);
    } else if (g.fifou.phase == FIFOU_WON) {
      fifouRenderFireworks(now);
    }
    delay(LOOP_MIN_PERIOD_MS);
    yield();
    return;
  }

  if (now - s_lastFrameMs < (unsigned long)LOOP_MIN_PERIOD_MS) {
    yield();
    return;
  }
  s_lastFrameMs = now;

  if (g.fifou.countdownActive) {
    unsigned long elapsed = now - g.fifou.countdownStartMs;
    unsigned long totalMs = (unsigned long)FIFOU_COUNTDOWN_SEC * 1000UL;
    if (elapsed >= totalMs) {
      fifouBeginSession(now);
    } else {
      fifouRenderCountdown(now);
    }
    delay(LOOP_MIN_PERIOD_MS);
    yield();
    return;
  }

  if (!g.fifou.sessionActive) {
    delay(LOOP_MIN_PERIOD_MS);
    yield();
    return;
  }

  float dtSec = (now - g.lastLoopMs) / 1000.0f;
  if (dtSec <= 0.0f) dtSec = 0.001f;
  if (dtSec > 0.15f) dtSec = 0.15f;
  g.lastLoopMs = now;

  MicSample mic;
  micSample(mic);
  int peak = micPeakEffective(mic.peak);
  g.lastPeak = peak;
  g.lastMicAvg = mic.avg;
  micUpdatePeakSmooth(peak);
  int peakEff = micPeakEffectifPourFlash(peak);
  g.currentState = ledStateWithHysteresis(peakEff, g.currentState);

  if (g.currentState == STATE_GREEN) {
    g.fifou.litLeds += g.fifou.gainRatePerSec * dtSec;
  } else if (g.currentState == STATE_RED) {
    g.fifou.litLeds -= g.fifou.lossRatePerSec * dtSec;
  }

  if (g.fifou.litLeds < 0.0f) g.fifou.litLeds = 0.0f;
  if (g.fifou.litLeds >= (float)LED_COUNT) {
    fifouFinishWin(now);
    delay(LOOP_MIN_PERIOD_MS);
    return;
  }

  fifouRenderStrip();

  if (now - g.fifou.sessionStartMs >= g.fifou.sessionDurMs) {
    fifouFinishLost(now);
  }

  delay(LOOP_MIN_PERIOD_MS);
  yield();
}

uint16_t defiFifouCountdownRemainSec() {
  if (!g.fifou.countdownActive) return 0;
  unsigned long elapsed = millis() - g.fifou.countdownStartMs;
  unsigned long totalMs = (unsigned long)FIFOU_COUNTDOWN_SEC * 1000UL;
  if (elapsed >= totalMs) return 0;
  return (uint16_t)((totalMs - elapsed + 999UL) / 1000UL);
}

uint32_t defiFifouSessionElapsedSec() {
  if (!g.fifou.sessionActive) return 0;
  return (millis() - g.fifou.sessionStartMs) / 1000UL;
}

uint32_t defiFifouSessionRemainSec() {
  if (!g.fifou.sessionActive) return 0;
  unsigned long elapsed = millis() - g.fifou.sessionStartMs;
  if (elapsed >= g.fifou.sessionDurMs) return 0;
  return (g.fifou.sessionDurMs - elapsed) / 1000UL;
}

int defiFifouLitLedsInt() {
  int lit = (int)(g.fifou.litLeds + 0.5f);
  if (lit < 0) lit = 0;
  if (lit > LED_COUNT) lit = LED_COUNT;
  return lit;
}
