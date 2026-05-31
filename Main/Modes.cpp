/*
 * Modes.cpp — Dispatch vers le mode actif (Config.h au boot, app web ensuite)
 */

#include "Modes.h"
#include "Config.h"
#include "AppState.h"
#include "ModeImmediat.h"
#include "ModeLent.h"
#include "LedStrip.h"
#include "WifiPortal.h"

void modesSetActive(uint8_t mode) {
  if (mode != MODE_IMMEDIAT && mode != MODE_LENT) {
    return;
  }
  g.live.activeMode = mode;
  g.transitionActive = false;
  g.currentState = STATE_GREEN;

  if (mode == MODE_LENT) {
    configApplyLent();
  } else {
    configApply();
  }
  liveApplyAttackRate();
  ledComputeZonesFromPlages();
}

void modesSetup() {
  liveConfigInit();
  modesSetActive(g.live.activeMode);

  if (g.live.activeMode == MODE_LENT) {
    modeLentSetup();
  } else {
    modeImmediatSetup();
  }
}

void modesLoop() {
  wifiPortalLoop();

  if (g.live.activeMode == MODE_LENT) {
    modeLentLoop();
  } else {
    modeImmediatLoop();
  }
}
