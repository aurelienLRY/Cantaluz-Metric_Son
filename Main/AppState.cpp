/*
 * AppState.cpp — Définition de la variable globale g et configApply()
 *
 * Contient :
 *   - g          : état global (voir AppState.h)
 *   - stateName  : noms français des paliers pour le debug
 *   - configApply: lit Config.h et remplit g.run via Convert.h
 */

#include "AppState.h"
#include "Convert.h"
#include "Config.h"
#include <string.h>

AppState g;

void liveConfigInit() {
  g.live.activeMode = MODE_ACTIF;
#if MODE_ACTIF == MODE_LENT
  g.live.maxBrightness = LENT_MAX_BRIGHTNESS;
  g.live.attackPercent = LENT_ATTACK_PERCENT;
#else
  g.live.maxBrightness = MAX_BRIGHTNESS;
  g.live.attackPercent = ATTACK_PERCENT;
#endif
  g.live.adcFinZoneVert = ADC_FIN_ZONE_VERT;
  g.live.adcFinZoneOrange = ADC_FIN_ZONE_ORANGE;
  g.lastPeak = 0;
  g.lastMicAvg = 0;
}

void liveApplyAttackRate() {
  g.run.attackRate = pctVersFraction(g.live.attackPercent);
}

static void liveLoadBrightnessAttackForMode() {
  if (g.live.activeMode == MODE_LENT) {
    g.live.maxBrightness = LENT_MAX_BRIGHTNESS;
    g.live.attackPercent = LENT_ATTACK_PERCENT;
  } else {
    g.live.maxBrightness = MAX_BRIGHTNESS;
    g.live.attackPercent = ATTACK_PERCENT;
  }
}

void liveConfigResetDefaults() {
  uint8_t prevMode = g.live.activeMode;
  g.live.adcFinZoneVert = ADC_FIN_ZONE_VERT;
  g.live.adcFinZoneOrange = ADC_FIN_ZONE_ORANGE;
  liveLoadBrightnessAttackForMode();
  g.live.activeMode = prevMode;
  if (prevMode == MODE_LENT) {
    configApplyLent();
  } else {
    configApply();
  }
  liveApplyAttackRate();
}

void liveResetField(const char *field) {
  if (!field || !field[0]) {
    return;
  }
  if (strcmp(field, "vert") == 0) {
    g.live.adcFinZoneVert = ADC_FIN_ZONE_VERT;
  } else if (strcmp(field, "orange") == 0) {
    g.live.adcFinZoneOrange = ADC_FIN_ZONE_ORANGE;
  } else if (strcmp(field, "bright") == 0) {
    g.live.maxBrightness = (g.live.activeMode == MODE_LENT)
      ? LENT_MAX_BRIGHTNESS : MAX_BRIGHTNESS;
  } else if (strcmp(field, "attack") == 0) {
    g.live.attackPercent = (g.live.activeMode == MODE_LENT)
      ? LENT_ATTACK_PERCENT : ATTACK_PERCENT;
    liveApplyAttackRate();
  }
  if (g.live.adcFinZoneOrange <= g.live.adcFinZoneVert) {
    g.live.adcFinZoneOrange = g.live.adcFinZoneVert + 1;
  }
}

const char *stateName(ColorState s) {
  switch (s) {
    case STATE_GREEN:  return "VERT";
    case STATE_ORANGE: return "ORANGE";
    case STATE_RED:    return "ROUGE";
  }
  return "?";
}

void configApply() {
  g.run.attackRate = pctVersFraction(g.live.attackPercent);
  g.run.avgSmooth = pctVersFraction(AVG_SMOOTH_PERCENT);
  g.run.peakSmoothFactor = pctVersFraction(PEAK_SMOOTH_PERCENT);
  g.run.descentDelayMs = secVersMs(DESCENT_DELAY_SEC);
  g.run.descentRate = dureeVersTauxDescente(DESCENT_DURATION_SEC);
  g.run.transitionCooldownMs = secVersMs(TRANSITION_COOLDOWN_SEC);
  g.run.bootStepMs = vitesseBootVersDelaiMs(BOOT_VU_SPEED_PERCENT);
}

void configApplyLent() {
  g.run.attackRate = pctVersFraction(g.live.attackPercent);
  g.run.avgSmooth = pctVersFraction(LENT_AVG_SMOOTH_PERCENT);
  g.run.peakSmoothFactor = pctVersFraction(LENT_PEAK_SMOOTH_PERCENT);
  g.run.descentDelayMs = secVersMs(LENT_DESCENT_DELAY_SEC);
  g.run.descentRate = dureeVersTauxDescente(LENT_DESCENT_DURATION_SEC);
  g.run.transitionCooldownMs = 0;
  g.run.bootStepMs = vitesseBootVersDelaiMs(LENT_BOOT_VU_SPEED_PERCENT);
}
