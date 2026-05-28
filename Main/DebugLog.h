#pragma once
/*
 * DebugLog.h — Logs moniteur série (optionnel)
 *
 * À quoi sert ce module ?
 * -----------------------
 * Affiche périodiquement peak, zone, état, flash en cours, LED allumées.
 *
 * Activé si : #define DEBUG_SERIAL dans Config.h
 * Vitesse : SERIAL_BAUD, intervalle DEBUG_INTERVAL_MS
 *
 * Si DEBUG_SERIAL est commenté, debugLogStatusIfDue() ne fait rien (stub inline).
 */

#include "Config.h"
#include "Types.h"

#ifdef DEBUG_SERIAL
void debugLogStatusIfDue(const MicSample &mic);
#else
inline void debugLogStatusIfDue(const MicSample &) {}
#endif
