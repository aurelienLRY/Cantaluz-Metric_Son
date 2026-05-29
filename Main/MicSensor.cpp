/*
 * MicSensor.cpp — Implémentation lecture micro et niveau VU
 *
 * Flux typique (chaque boucle) :
 *   micSample → micUpdatePeakSmooth → micUpdateDisplayLevel
 * FlashEtat utilise en plus micPeakEffectifPourFlash.
 */

#include "MicSensor.h"
#include "AppState.h"
#include "Config.h"
#include "LedStrip.h"

void micSample(MicSample &out) {
  uint32_t sum = 0;
  out.minVal = 1023;
  out.maxVal = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    int v = analogRead(MIC_PIN);
    sum += v;
    if (v < out.minVal) out.minVal = v;
    if (v > out.maxVal) out.maxVal = v;
    delayMicroseconds(SAMPLE_DELAY_US);
    if ((i & 15) == 15) {
      yield();
    }
  }

  out.avg = (int)(sum / SAMPLE_COUNT);
  out.peak = out.maxVal - out.minVal;
  out.raw = analogRead(MIC_PIN);
}

void micUpdatePeakSmooth(int peak) {
  g.peakSmooth += ((float)peak - g.peakSmooth) * g.run.peakSmoothFactor;
}

int micPeakEffectifPourFlash(int peak) {
  int p = peak;
  int lisse = (int)g.peakSmooth;
  if (lisse > p) {
    p = lisse;
  }
  return p;
}

float micPeakToLevel(int peak) {
  float level = (float)(peak - ADC_VU_MIN) / (float)(g.vuMaxPeak - ADC_VU_MIN);
  if (level < 0.0f) level = 0.0f;
  if (level > 1.0f) level = 1.0f;
  return level;
}

void micUpdateDisplayLevel(int peak, float dtSec) {
  g.peakAverage += ((float)peak - g.peakAverage) * g.run.avgSmooth;
  float target = micPeakToLevel(peak);
  unsigned long now = millis();

  if ((float)peak >= g.peakAverage) {
    g.belowAvgSinceMs = 0;
    if (target > g.displayLevel) {
      g.displayLevel += (target - g.displayLevel) * g.run.attackRate;
    } else {
      g.displayLevel += (target - g.displayLevel) * (g.run.attackRate * 0.5f);
    }
  } else {
    if (g.belowAvgSinceMs == 0) g.belowAvgSinceMs = now;
    if (now - g.belowAvgSinceMs >= g.run.descentDelayMs) {
      g.displayLevel -= g.run.descentRate * dtSec;
      if (g.displayLevel < target) g.displayLevel = target;
    }
  }

  float minLevel = (float)MIN_LEDS_ON / (float)LED_COUNT;
  if (g.displayLevel < minLevel) g.displayLevel = minLevel;
  if (g.displayLevel > 1.0f) g.displayLevel = 1.0f;
}

void micCalibrateVuMax() {
  int ambientMax = 0;
  unsigned long endMs = millis() + CALIBRATE_MS;

#ifdef DEBUG_SERIAL
  Serial.println(F("Calibration silence (barre pleine)..."));
#endif

  while (millis() < endMs) {
    MicSample m;
    micSample(m);
    if (m.peak > ambientMax) ambientMax = m.peak;
    ledRenderVuMeter((float)MIN_LEDS_ON / (float)LED_COUNT);
    delay(15);
    yield();
    ESP.wdtFeed();
  }

  if (ambientMax < 8) ambientMax = 40;

  g.vuMaxPeak = ambientMax + CAL_VU_MARGIN;
  if (MANUAL_VU_MAX > 0) g.vuMaxPeak = MANUAL_VU_MAX;
  if (g.vuMaxPeak < 120) g.vuMaxPeak = 120;

  g.peakAverage = (float)ambientMax;
  g.peakSmooth = (float)ambientMax;

#ifdef DEBUG_SERIAL
  Serial.print(F("Bruit fond peak="));
  Serial.println(ambientMax);
  Serial.print(F("Barre pleine si peak>="));
  Serial.println(g.vuMaxPeak);
#endif
}
