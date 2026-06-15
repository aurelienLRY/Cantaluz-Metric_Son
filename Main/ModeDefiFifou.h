#pragma once
/*
 * ModeDefiFifou.h — Défi Fifou (jeu du calme)
 *
 * Les élèves partent avec FIFOU_START_LEDS LED d'une couleur dédiée.
 * Zone calme → gain ; orange → statu quo ; rouge → perte (plus lente).
 * Victoire si le bandeau est rempli avant la fin du temps choisi (2 / 5 / 10 min).
 */

#include <Arduino.h>
#include "AppState.h"

void modeDefiFifouSetup();
void modeDefiFifouLoop();

bool defiFifouStart(uint16_t durSec);
void defiFifouStop();

const char *defiFifouPhaseLabel(FifouPhase phase);

uint16_t defiFifouCountdownRemainSec();
uint32_t defiFifouSessionElapsedSec();
uint32_t defiFifouSessionRemainSec();
int defiFifouLitLedsInt();
