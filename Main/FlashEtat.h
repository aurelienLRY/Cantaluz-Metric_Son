#pragma once
/*
 * FlashEtat.h — Flashs bleus et paliers vert → orange → rouge
 *
 * À quoi sert ce module ?
 * -----------------------
 * Quand le son monte d'un palier (vert→orange ou orange→rouge) :
 *   - série de flashs bleus sur tout le ruban,
 *   - un seul cran à la fois (pas de flash à la descente).
 *
 * Réglages liés : Config.h section FLASH BLEU
 * Utilise : LedStrip (affichage), MicSensor (peak lissé), Types (ColorState)
 */

#include "Types.h"

// Permet de calculer le prochain palier lors d'une montée (currentState + 1 max)
ColorState flashProchainEtatMontee(ColorState zonePlage);

// Permet de démarrer les flashs bleus vers newState (orange ou rouge)
void flashStartTransition(ColorState newState);

// Permet d'avancer l'animation flash ; retourne true quand la série est terminée
bool flashUpdateTransition();

// Permet de gérer montée (flash) et descente (hystérésis sans flash) à chaque boucle
void flashHandleStateMachine(int peak);
