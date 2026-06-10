#pragma once
/*
 * LedStrip.h — Ruban WS2812B (zones couleur, VU, boot visuel)
 *
 * À quoi sert ce module ?
 * -----------------------
 *   - Répartir vert / orange / rouge le long du ruban (proportionnel aux plages ADC)
 *   - Afficher la barre VU depuis le début DIN
 *   - Animations boot (bleu plein, montée/descente verte)
 *
 * Réglages liés : Config.h sections BANDEAU et PLAGES ADC
 * Matériel : LED_PIN (D2), FastLED, g.leds[] dans AppState
 */

#include <FastLED.h>
#include "Types.h"

// Couleurs fixes des trois zones (modifiables dans LedStrip.cpp si besoin)
extern const CRGB COULEUR_VERT;
extern const CRGB COULEUR_ORANGE;
extern const CRGB COULEUR_ROUGE;

// Permet de calculer g.ledFinZoneVert/Orange et les seuils flash depuis ADC_FIN_ZONE_*
void ledComputeZonesFromPlages();

// Permet de savoir si le peak est en zone verte, orange ou rouge (sans hystérésis)
ColorState ledZoneDepuisPeak(int peak);

// Permet de redescendre d'état sans rebond (utilise ADC_HYST_VERT / ADC_HYST_ORANGE)
ColorState ledStateWithHysteresis(int peak, ColorState cur);

// Permet de colorer une LED selon sa position sur le ruban (pas selon le volume instantané)
CRGB ledCouleurPourIndex(int index);

// Permet d'allumer litCount LED depuis le début avec les couleurs de zone
void ledRenderVuMeter(float level);

// Permet de remplir tout le ruban d'une couleur (flash bleu, etc.)
void ledFillStrip(CRGB color);

// Permet d'afficher le ruban bleu pendant dureeMs puis attendre (boot)
void ledAfficherBleuComplet(uint16_t dureeMs);

// Permet d'initialiser FastLED (appeler une fois au boot)
void ledInitHardware();

// Permet de jouer l'animation montée/descente verte au démarrage
void ledRunBootSequence();
