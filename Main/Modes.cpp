/*
 * Modes.cpp — Dispatch vers le mode actif (Config.h au boot, app web ensuite)
 */

#include "Modes.h"
#include "Config.h"
#include "AppState.h"
#include "ModeImmediat.h"
#include "ModeLent.h"
#include "ModeMeditation.h"
#include "ModeDefiFifou.h"
#include "LedStrip.h"
#include "WifiPortal.h"

void modesSetActive(uint8_t mode) {
  if (mode != MODE_IMMEDIAT && mode != MODE_LENT && mode != MODE_MEDITATION
      && mode != MODE_DEFI_FIFOU) {
    return;
  }

  if (g.live.activeMode == MODE_MEDITATION && mode != MODE_MEDITATION) {
    meditationStop();
  }
  if (g.live.activeMode == MODE_DEFI_FIFOU && mode != MODE_DEFI_FIFOU) {
    defiFifouStop();
  }

  g.live.activeMode = mode;
  g.transitionActive = false;
  g.currentState = STATE_GREEN;

  if (mode == MODE_LENT) {
    configApplyLent();
  } else if (mode == MODE_MEDITATION) {
    configApply();
    modeMeditationSetup();
  } else if (mode == MODE_DEFI_FIFOU) {
    configApply();
    modeDefiFifouSetup();
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
  } else if (g.live.activeMode == MODE_MEDITATION) {
    modeMeditationSetup();
  } else if (g.live.activeMode == MODE_DEFI_FIFOU) {
    modeDefiFifouSetup();
  } else {
    modeImmediatSetup();
  }
}

void modesLoop() {
  wifiPortalLoop();

  if (g.live.activeMode == MODE_MEDITATION) {
    modeMeditationLoop();
  } else if (g.live.activeMode == MODE_DEFI_FIFOU) {
    modeDefiFifouLoop();
  } else if (g.live.activeMode == MODE_LENT) {
    modeLentLoop();
  } else {
    modeImmediatLoop();
  }
}
