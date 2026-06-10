#pragma once
/*
 * MicSensor.h — Micro MAX4466 (lecture, niveau barre, sensibilité app)
 */

#include "Types.h"

// Applique g.live.sensitivity → g.micGate, g.micSpan, g.micDeadband
void micApplySensitivity();

// Initialise barre VU au boot (sans calibration silence)
void micInitVuFromSettings();

// Peak corrigé (porte selon sensibilité)
int micPeakEffective(int rawPeak);

void micSample(MicSample &out);
void micUpdatePeakSmooth(int peak);
int micPeakEffectifPourFlash(int peak);
float micPeakToLevel(int peak);
void micUpdateDisplayLevel(int peak, float dtSec);
