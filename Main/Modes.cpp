/*
 * Modes.cpp — Dispatch vers le mode défini par MODE_ACTIF (Config.h)
 *
 * Si compilation échoue avec « MODE_ACTIF inconnu » :
 *   vérifier que MODE_ACTIF vaut MODE_IMMEDIAT dans Config.h
 */

#include "Modes.h"
#include "Config.h"
#include "ModeImmediat.h"
#include "ModeLent.h"

void modesSetup() {
#if MODE_ACTIF == MODE_IMMEDIAT
  modeImmediatSetup();
#elif MODE_ACTIF == MODE_LENT
  modeLentSetup();
#else
#error "MODE_ACTIF inconnu — utiliser MODE_IMMEDIAT ou MODE_LENT dans Config.h"
#endif
}

void modesLoop() {
#if MODE_ACTIF == MODE_IMMEDIAT
  modeImmediatLoop();
#elif MODE_ACTIF == MODE_LENT
  modeLentLoop();
#else
#error "MODE_ACTIF inconnu"
#endif
}
