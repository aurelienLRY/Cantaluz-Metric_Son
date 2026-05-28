/*
 * Modes.cpp — Dispatch vers le mode défini par MODE_ACTIF (Config.h)
 *
 * Si compilation échoue avec « MODE_ACTIF inconnu » :
 *   vérifier que MODE_ACTIF vaut MODE_IMMEDIAT dans Config.h
 */

#include "Modes.h"
#include "Config.h"
#include "ModeImmediat.h"

void modesSetup() {
#if MODE_ACTIF == MODE_IMMEDIAT
  modeImmediatSetup();
#else
#error "MODE_ACTIF inconnu — definir MODE_IMMEDIAT dans Config.h"
#endif
}

void modesLoop() {
#if MODE_ACTIF == MODE_IMMEDIAT
  modeImmediatLoop();
#else
#error "MODE_ACTIF inconnu"
#endif
}
