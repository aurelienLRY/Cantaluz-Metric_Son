/*
 * ModeMeditation.cpp — Respiration guidée sur le ruban WS2812B
 */

#include "ModeMeditation.h"
#include "Config.h"
#include "LedStrip.h"
#include "AppState.h"

struct MedProfile {
  uint16_t sessionSec;
  uint8_t inspireSec;
  uint8_t holdSec;
  uint8_t expireSec;
  uint8_t holdEmptySec;
  uint8_t pauseSec;
};

static const MedProfile MED_PROFILES[] = {
  { MEDIT_DUR_2MIN_SEC,  MEDIT_P0_INSPIRE_SEC, MEDIT_P0_HOLD_SEC, MEDIT_P0_EXPIRE_SEC, MEDIT_P0_HOLD_EMPTY_SEC, MEDIT_P0_PAUSE_SEC },
  { MEDIT_DUR_5MIN_SEC,  MEDIT_P1_INSPIRE_SEC, MEDIT_P1_HOLD_SEC, MEDIT_P1_EXPIRE_SEC, MEDIT_P1_HOLD_EMPTY_SEC, MEDIT_P1_PAUSE_SEC },
  { MEDIT_DUR_10MIN_SEC, MEDIT_P2_INSPIRE_SEC, MEDIT_P2_HOLD_SEC, MEDIT_P2_EXPIRE_SEC, MEDIT_P2_HOLD_EMPTY_SEC, MEDIT_P2_PAUSE_SEC },
};
static const uint8_t MED_PROFILE_COUNT = sizeof(MED_PROFILES) / sizeof(MED_PROFILES[0]);

static const CRGB MED_COL_IN     = CRGB(MEDIT_COLOR_IN_R,    MEDIT_COLOR_IN_G,    MEDIT_COLOR_IN_B);
static const CRGB MED_COL_HOLD   = CRGB(MEDIT_COLOR_HOLD_R,  MEDIT_COLOR_HOLD_G,  MEDIT_COLOR_HOLD_B);
static const CRGB MED_COL_OUT    = CRGB(MEDIT_COLOR_OUT_R,   MEDIT_COLOR_OUT_G,   MEDIT_COLOR_OUT_B);
static const CRGB MED_COL_EMPTY  = CRGB(MEDIT_COLOR_EMPTY_R, MEDIT_COLOR_EMPTY_G, MEDIT_COLOR_EMPTY_B);
static const CRGB MED_COL_DONE   = CRGB(MEDIT_COLOR_DONE_R,  MEDIT_COLOR_DONE_G,  MEDIT_COLOR_DONE_B);

static int medProfileIndexFromDur(uint16_t durSec) {
  if (durSec <= MEDIT_DUR_2MIN_SEC + 30) return 0;
  if (durSec <= MEDIT_DUR_5MIN_SEC + 30) return 1;
  return 2;
}

static const MedProfile *medCurrentProfile() {
  if (g.med.durProfile >= MED_PROFILE_COUNT) {
    g.med.durProfile = 0;
  }
  return &MED_PROFILES[g.med.durProfile];
}

static void medSegmentCounts(int *nIn, int *nHold, int *nOut, int *nEmpty) {
  const MedProfile *p = medCurrentProfile();
  int breathTotal = p->inspireSec + p->holdSec + p->expireSec + p->holdEmptySec;
  if (breathTotal < 1) breathTotal = 1;

  *nIn = (LED_COUNT * (long)p->inspireSec) / breathTotal;
  *nHold = (LED_COUNT * (long)p->holdSec) / breathTotal;
  *nEmpty = (LED_COUNT * (long)p->holdEmptySec) / breathTotal;
  *nOut = LED_COUNT - *nIn - *nHold - *nEmpty;

  if (*nIn < 1) *nIn = 1;
  if (*nHold < 1) *nHold = 1;
  if (*nOut < 1) *nOut = 1;
  if (*nEmpty < 1) *nEmpty = 1;

  int sum = *nIn + *nHold + *nOut + *nEmpty;
  if (sum > LED_COUNT) {
    *nOut -= (sum - LED_COUNT);
    if (*nOut < 1) *nOut = 1;
  } else if (sum < LED_COUNT) {
    *nOut += (LED_COUNT - sum);
  }
}

static CRGB medColorForPhase(MedPhase phase) {
  switch (phase) {
    case MED_INSPIRE:    return MED_COL_IN;
    case MED_HOLD:       return MED_COL_HOLD;
    case MED_EXPIRE:     return MED_COL_OUT;
    case MED_HOLD_EMPTY: return MED_COL_EMPTY;
    default:             return CRGB::Black;
  }
}

static void medClearStrip() {
  fill_solid(g.leds, LED_COUNT, CRGB::Black);
  FastLED.show();
  yield();
}

static void medComputePhaseBounds(MedPhase phase, int *outStart, int *outEnd, uint16_t *outMsPerLed) {
  const MedProfile *p = medCurrentProfile();
  int nIn, nHold, nOut, nEmpty;
  medSegmentCounts(&nIn, &nHold, &nOut, &nEmpty);

  int start = 0;
  int end = 0;
  uint8_t phaseSec = 1;

  switch (phase) {
    case MED_INSPIRE:
      start = 0;
      end = nIn;
      phaseSec = p->inspireSec;
      break;
    case MED_HOLD:
      start = nIn;
      end = nIn + nHold;
      phaseSec = p->holdSec;
      break;
    case MED_EXPIRE:
      start = nIn + nHold;
      end = nIn + nHold + nOut;
      phaseSec = p->expireSec;
      break;
    case MED_HOLD_EMPTY:
      start = nIn + nHold + nOut;
      end = LED_COUNT;
      phaseSec = p->holdEmptySec;
      break;
    default:
      start = 0;
      end = 0;
      phaseSec = 1;
      break;
  }

  int count = end - start;
  if (count < 1) count = 1;

  *outStart = start;
  *outEnd = end;
  *outMsPerLed = (uint16_t)((phaseSec * 1000UL) / (unsigned)count);
  if (*outMsPerLed < 8) *outMsPerLed = 8;
}

static void medBeginBreathCycle(unsigned long now) {
  g.med.phase = MED_INSPIRE;
  g.med.phaseStartMs = now;
  g.med.cycleLedIndex = 0;
  g.med.nextLedStepMs = now;

  int start, end;
  uint16_t ms;
  medComputePhaseBounds(MED_INSPIRE, &start, &end, &ms);
  g.med.phaseEndLed = end;
  g.med.msPerLed = ms;
  (void)start;

  medClearStrip();
}

static void medEnterPhase(MedPhase phase, unsigned long now) {
  g.med.phase = phase;
  g.med.phaseStartMs = now;
  g.med.nextLedStepMs = now;

  if (phase == MED_PAUSE) {
    medClearStrip();
    return;
  }

  int start, end;
  uint16_t ms;
  medComputePhaseBounds(phase, &start, &end, &ms);
  g.med.phaseEndLed = end;
  g.med.msPerLed = ms;
  g.med.cycleLedIndex = start;
}

static void medFinishSession() {
  g.med.sessionActive = false;
  g.med.countdownActive = false;
  g.med.phase = MED_DONE;
  ledFillStrip(MED_COL_DONE);
  delay(2500);
  medClearStrip();
  g.med.phase = MED_IDLE;
}

const char *meditationPhaseLabel(MedPhase phase) {
  switch (phase) {
    case MED_IDLE:       return "idle";
    case MED_COUNTDOWN:  return "countdown";
    case MED_INSPIRE:    return "inspire";
    case MED_HOLD:       return "hold";
    case MED_EXPIRE:     return "expire";
    case MED_HOLD_EMPTY: return "holdempty";
    case MED_PAUSE:      return "pause";
    case MED_DONE:       return "done";
  }
  return "idle";
}

void meditationStop() {
  g.med.sessionActive = false;
  g.med.countdownActive = false;
  g.med.phase = MED_IDLE;
  medClearStrip();
}

bool meditationStart(uint16_t durSec) {
  g.med.durProfile = medProfileIndexFromDur(durSec);
  const MedProfile *p = medCurrentProfile();
  g.med.sessionDurMs = (uint32_t)p->sessionSec * 1000UL;
  g.med.sessionActive = false;
  g.med.countdownActive = true;
  g.med.phase = MED_COUNTDOWN;
  g.med.countdownStartMs = millis();
  medClearStrip();
  return true;
}

void modeMeditationSetup() {
  meditationStop();
  g.med.durProfile = 0;
  g.med.sessionDurMs = (uint32_t)MEDIT_DUR_2MIN_SEC * 1000UL;
  ledComputeZonesFromPlages();
  ledInitHardware();
  FastLED.setBrightness(g.live.maxBrightness);
  medClearStrip();
}

static void medRenderCountdown(unsigned long now) {
  unsigned long elapsed = now - g.med.countdownStartMs;
  unsigned long totalMs = (unsigned long)MEDIT_COUNTDOWN_SEC * 1000UL;
  if (elapsed >= totalMs) return;

  unsigned long remain = totalMs - elapsed;
  int lit = 1 + (int)((totalMs - remain) * (LED_COUNT - 1) / totalMs);
  if (lit > LED_COUNT) lit = LED_COUNT;
  if (lit < 1) lit = 1;

  CRGB c = CRGB(80, 40, 120);
  for (int i = 0; i < LED_COUNT; i++) {
    g.leds[i] = (i < lit) ? c : CRGB::Black;
  }
  FastLED.show();
  yield();
}

static void medPulseHoldSections(unsigned long now) {
  if (g.med.phase != MED_HOLD && g.med.phase != MED_HOLD_EMPTY) return;

  int start, end;
  uint16_t ms;
  medComputePhaseBounds(g.med.phase, &start, &end, &ms);
  (void)ms;

  CRGB base = medColorForPhase(g.med.phase);
  uint8_t pulse = ((now / 450UL) & 1) ? 220 : 160;
  for (int i = start; i < g.med.cycleLedIndex && i < end; i++) {
    CRGB c = base;
    c.nscale8_video(pulse);
    g.leds[i] = c;
  }
}

static void medStepBreath(unsigned long now) {
  if (g.med.phase == MED_PAUSE) {
    const MedProfile *p = medCurrentProfile();
    unsigned long pauseMs = (unsigned long)p->pauseSec * 1000UL;
    if (now - g.med.phaseStartMs >= pauseMs) {
      if (now - g.med.sessionStartMs >= g.med.sessionDurMs) {
        medFinishSession();
        return;
      }
      medBeginBreathCycle(now);
    }
    return;
  }

  if (g.med.cycleLedIndex >= g.med.phaseEndLed) {
    if (g.med.phase == MED_INSPIRE) {
      medEnterPhase(MED_HOLD, now);
    } else if (g.med.phase == MED_HOLD) {
      medEnterPhase(MED_EXPIRE, now);
    } else if (g.med.phase == MED_EXPIRE) {
      medEnterPhase(MED_HOLD_EMPTY, now);
    } else if (g.med.phase == MED_HOLD_EMPTY) {
      medEnterPhase(MED_PAUSE, now);
    }
    return;
  }

  if (now < g.med.nextLedStepMs) {
    medPulseHoldSections(now);
    FastLED.show();
    yield();
    return;
  }

  CRGB col = medColorForPhase(g.med.phase);
  if (g.med.cycleLedIndex >= 0 && g.med.cycleLedIndex < LED_COUNT) {
    g.leds[g.med.cycleLedIndex] = col;
  }
  g.med.cycleLedIndex++;
  g.med.nextLedStepMs = now + g.med.msPerLed;

  medPulseHoldSections(now);
  FastLED.show();
  yield();
}

void modeMeditationLoop() {
  unsigned long now = millis();

  if (g.med.countdownActive) {
    unsigned long elapsed = now - g.med.countdownStartMs;
    unsigned long totalMs = (unsigned long)MEDIT_COUNTDOWN_SEC * 1000UL;
    if (elapsed >= totalMs) {
      g.med.countdownActive = false;
      g.med.sessionActive = true;
      g.med.sessionStartMs = now;
      medBeginBreathCycle(now);
    } else {
      medRenderCountdown(now);
    }
    delay(LOOP_MIN_PERIOD_MS);
    yield();
    return;
  }

  if (!g.med.sessionActive) {
    delay(LOOP_MIN_PERIOD_MS);
    yield();
    return;
  }

  if (now - g.med.sessionStartMs >= g.med.sessionDurMs) {
    medFinishSession();
    delay(LOOP_MIN_PERIOD_MS);
    return;
  }

  medStepBreath(now);
  delay(LOOP_MIN_PERIOD_MS);
  yield();
}

uint16_t meditationCountdownRemainSec() {
  if (!g.med.countdownActive) return 0;
  unsigned long elapsed = millis() - g.med.countdownStartMs;
  unsigned long totalMs = (unsigned long)MEDIT_COUNTDOWN_SEC * 1000UL;
  if (elapsed >= totalMs) return 0;
  return (uint16_t)((totalMs - elapsed + 999UL) / 1000UL);
}

uint32_t meditationSessionElapsedSec() {
  if (!g.med.sessionActive) return 0;
  return (millis() - g.med.sessionStartMs) / 1000UL;
}

uint32_t meditationSessionRemainSec() {
  if (!g.med.sessionActive) return 0;
  unsigned long elapsed = millis() - g.med.sessionStartMs;
  if (elapsed >= g.med.sessionDurMs) return 0;
  return (g.med.sessionDurMs - elapsed) / 1000UL;
}
