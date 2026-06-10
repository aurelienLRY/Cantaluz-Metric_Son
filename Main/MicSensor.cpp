/*
 * MicSensor.cpp — Lecture micro et niveau VU (sensibilité via l'app)
 */

#include "MicSensor.h"
#include "AppState.h"
#include "Config.h"
#include "LedStrip.h"

void micApplySensitivity() {
  uint8_t s = g.live.sensitivity;
  if (s > 100) s = 100;

  g.micGate = MIC_SENS_GATE_MAX
    - ((int)s * (MIC_SENS_GATE_MAX - MIC_SENS_GATE_MIN)) / 100;
  g.micSpan = MIC_SENS_SPAN_MAX
    - ((int)s * (MIC_SENS_SPAN_MAX - MIC_SENS_SPAN_MIN)) / 100;
  g.micDeadband = MIC_SENS_DB_MAX
    - ((int)s * (MIC_SENS_DB_MAX - MIC_SENS_DB_MIN)) / 100;

  if (g.micSpan < 80) g.micSpan = 80;
  g.vuMaxPeak = g.micSpan;
}

void micInitVuFromSettings() {
  micApplySensitivity();
  g.peakAverage = 0.0f;
  g.peakSmooth = 0.0f;
  g.displayLevel = (float)MIN_LEDS_ON / (float)LED_COUNT;
  g.belowAvgSinceMs = 0;
}

int micPeakEffective(int rawPeak) {
  int p = rawPeak - g.micGate;
  if (p < 0) p = 0;
  return p;
}

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
  int span = g.micSpan;
  if (span < 60) span = 60;

  float level = (float)peak / (float)span;
  if (level < 0.0f) level = 0.0f;
  if (level > 1.0f) level = 1.0f;
  return level;
}

void micUpdateDisplayLevel(int peak, float dtSec) {
  if (peak <= g.micDeadband) {
    peak = 0;
  }

  g.peakAverage += ((float)peak - g.peakAverage) * g.run.avgSmooth;
  float target = micPeakToLevel(peak);
  unsigned long now = millis();
  float dbHalf = (float)g.micDeadband * 0.5f;

  if ((float)peak > g.peakAverage + dbHalf) {
    g.belowAvgSinceMs = 0;
    if (target > g.displayLevel) {
      g.displayLevel += (target - g.displayLevel) * g.run.attackRate;
    } else {
      g.displayLevel += (target - g.displayLevel) * (g.run.attackRate * 0.35f);
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
