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

AppState g;

const char *stateName(ColorState s) {
  switch (s) {
    case STATE_GREEN:  return "VERT";
    case STATE_ORANGE: return "ORANGE";
    case STATE_RED:    return "ROUGE";
  }
  return "?";
}

void configApply() {
  g.run.attackRate = pctVersFraction(ATTACK_PERCENT);
  g.run.avgSmooth = pctVersFraction(AVG_SMOOTH_PERCENT);
  g.run.peakSmoothFactor = pctVersFraction(PEAK_SMOOTH_PERCENT);
  g.run.descentDelayMs = secVersMs(DESCENT_DELAY_SEC);
  g.run.descentRate = dureeVersTauxDescente(DESCENT_DURATION_SEC);
  g.run.transitionCooldownMs = secVersMs(TRANSITION_COOLDOWN_SEC);
  g.run.bootStepMs = vitesseBootVersDelaiMs(BOOT_VU_SPEED_PERCENT);
}

void configApplyLent() {
  g.run.attackRate = pctVersFraction(LENT_ATTACK_PERCENT);
  g.run.avgSmooth = pctVersFraction(LENT_AVG_SMOOTH_PERCENT);
  g.run.peakSmoothFactor = pctVersFraction(LENT_PEAK_SMOOTH_PERCENT);
  g.run.descentDelayMs = secVersMs(LENT_DESCENT_DELAY_SEC);
  g.run.descentRate = dureeVersTauxDescente(LENT_DESCENT_DURATION_SEC);
  g.run.transitionCooldownMs = 0;
  g.run.bootStepMs = vitesseBootVersDelaiMs(LENT_BOOT_VU_SPEED_PERCENT);
}
