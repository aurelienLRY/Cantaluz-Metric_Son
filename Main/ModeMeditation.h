#pragma once
/*
 * ModeMeditation.h — Méditation guidée (respiration par le ruban)
 *
 * Les LED s'allument une par une dans le même sens (DIN → fin).
 * Inspire (cyan) → Retiens (ambre) → Expire (magenta) → pause → cycle suivant.
 * Durées 2 / 5 / 10 min choisies dans l'app ; compte à rebours avant démarrage.
 */

#include <Arduino.h>
#include "AppState.h"

void modeMeditationSetup();
void modeMeditationLoop();

// Démarre le compte à rebours puis la séance (durSec = 120, 300 ou 600)
bool meditationStart(uint16_t durSec);

// Arrête la séance en cours
void meditationStop();

// Libellé phase pour l'API / l'app
const char *meditationPhaseLabel(MedPhase phase);

uint16_t meditationCountdownRemainSec();
uint32_t meditationSessionElapsedSec();
uint32_t meditationSessionRemainSec();
