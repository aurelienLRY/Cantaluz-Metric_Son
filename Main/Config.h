#pragma once
/*
 * Config.h — Paramètres utilisateur Cantaluz
 *
 * Où régler quoi ?
 * ----------------
 *   Carte / matériel / méditation / Wi-Fi  → ici (Config.h)
 *   En classe, à la volée                  → app Réglages (LiveConfig, voir ci-dessous)
 *
 * Correspondance app ↔ Config.h (valeurs par défaut au boot) :
 *
 *   App Réglages          Config.h (défaut)
 *   ─────────────────     ─────────────────────────────
 *   Sensibilité           DEFAULT_SENSITIVITY (+ MIC_SENS_* = formule interne)
 *   Zone calme            ADC_FIN_ZONE_VERT
 *   Zone animée           ADC_FIN_ZONE_ORANGE
 *   Luminosité            MAX_BRIGHTNESS ou LENT_MAX_BRIGHTNESS selon le mode
 *   Montée de la barre    ATTACK_PERCENT ou LENT_ATTACK_PERCENT selon le mode
 *
 * Deux jeux « montée / descente / lissage » existent volontairement :
 *   • sans préfixe     → mode Flash  (MODE_IMMEDIAT)
 *   • préfixe LENT_*   → mode Standard (MODE_LENT)
 * Ce ne sont pas des doublons : chaque mode a son comportement.
 *
 * Format :  // Description   value: [min - max]
 */

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════
//  MODE AU DÉMARRAGE
// ═══════════════════════════════════════════════════════════════
#define MODE_IMMEDIAT    0   // Flash
#define MODE_LENT        1   // Standard
#define MODE_MEDITATION  2   // Méditation guidée
#define MODE_ACTIF       MODE_IMMEDIAT   // value: [MODE_IMMEDIAT | MODE_LENT | MODE_MEDITATION]

// ═══════════════════════════════════════════════════════════════
//  RUBAN WS2812B
// ═══════════════════════════════════════════════════════════════
#define LEDS_PER_METER    55
#define STRIP_LENGTH_M     5
#define LED_COUNT          (LEDS_PER_METER * STRIP_LENGTH_M)  // test court : mettre 17
#define LED_PIN            4     // D2 sur WeMos D1
#define MIN_LEDS_ON        5     // LED allumées minimum au silence   value: [1 - 50]

// ═══════════════════════════════════════════════════════════════
//  MICRO — matériel + sensibilité (app : curseur Sensibilité)
// ═══════════════════════════════════════════════════════════════
#define MIC_PIN              A0
#define SAMPLE_COUNT         24    // 64 possible sans Wi-Fi   value: [8 - 256]
#define SAMPLE_DELAY_US      200   // value: [50 - 1000]

#define DEFAULT_SENSITIVITY  8     // Défaut curseur app 0–100   value: [0 - 100]

// ── Cartographie curseur Sensibilité (app) → micro (MicSensor.cpp) ──
// s = g.live.sensitivity (0 = peu sensible, 100 = très sensible)
//
//   micGate     = MIC_SENS_GATE_MAX - s × (MAX - MIN) / 100
//   micSpan     = MIC_SENS_SPAN_MAX - s × (MAX - MIN) / 100
//   micDeadband = MIC_SENS_DB_MAX - s × (MAX - MIN) / 100
//
//   eff = max(0, raw - micGate)          ← peak utilisé (moniteur : « eff »)
//   barre % = eff / micSpan              ← hauteur vu-mètre
//
// Exemples (raw = variation max-min du micro sur une mesure) :
//   s=0  → gate 110, span 720 : raw 100 → eff 0 ; raw 200 → barre ~12 %
//   s=8  → gate 102, span 680 : raw 25  → eff 0 (silence typique)
//   s=100→ gate 10,  span 220 : raw 50  → eff 40 → barre ~18 %
//
#define MIC_SENS_GATE_MIN    10    // Porte (gate) quand s=100 : bruit minimal filtré   value: [0 - 80]
#define MIC_SENS_GATE_MAX    110   // Porte quand s=0 : ignore davantage le bruit de fond   value: [50 - 200]
#define MIC_SENS_SPAN_MIN    220   // Peak eff. pour barre 100 % quand s=100 (voix proche)   value: [100 - 400]
#define MIC_SENS_SPAN_MAX    720   // Peak eff. pour barre 100 % quand s=0 (voix très forte)   value: [400 - 900]
#define MIC_SENS_DB_MIN      8     // Zone morte barre quand s=100 (montée facile)   value: [0 - 20]
#define MIC_SENS_DB_MAX      35     // Zone morte quand s=0 (barre stable au silence)   value: [15 - 60]
// Ne pas confondre avec ADC_FIN_ZONE_VERT / ORANGE (Zone calme / animée sur le ruban).

// ═══════════════════════════════════════════════════════════════
//  COULEURS SUR LE RUBAN + FLASHS BLEUS (app : Zone calme / Zone animée)
//  Peak EFFECTIF (eff) après porte de sensibilité — pas le raw du moniteur série.
//  Répartition vert|orange|rouge le long du bandeau : proportion de ces seuils.
// ═══════════════════════════════════════════════════════════════
#define ADC_PLAGE_MIN        0
#define ADC_PLAGE_MAX        1023
#define ADC_FIN_ZONE_VERT    400   // = Zone calme (défaut app)   value: [0 - 1022]
#define ADC_FIN_ZONE_ORANGE  700   // = Zone animée (défaut app)   value: [vert+1 - 1023]
#define ADC_HYST_VERT        80    // Anti-rebond descente palier   value: [0 - 500]
#define ADC_HYST_ORANGE      80

// ═══════════════════════════════════════════════════════════════
//  MODE FLASH — VU + flashs bleus (MODE_IMMEDIAT)
// ═══════════════════════════════════════════════════════════════
#define MAX_BRIGHTNESS           100    // = Luminosité app (mode Flash)   value: [0 - 255]
#define ATTACK_PERCENT           8    // = Montée barre app (mode Flash)   value: [0 - 100]
#define AVG_SMOOTH_PERCENT       30    // Lissage moyenne peak   value: [0 - 100]
#define PEAK_SMOOTH_PERCENT      10    // Lissage paliers / flash   value: [0 - 100]
#define DESCENT_DELAY_SEC        1    // Attente avant descente barre   value: [0 - 120]
#define DESCENT_DURATION_SEC     4    // Durée pour vider la barre   value: [1 - 600]

#define STATE_HOLD_MS            450   // Maintien seuil avant flash   value: [0 - 5000]
#define FLASH_HOLD_RESET_MS      400   // value: [0 - 5000]
#define TRANSITION_COOLDOWN_SEC  3     // Entre deux séries de flashs   value: [0 - 10]
#define FLASH_COUNT              3     // value: [1 - 20]
#define FLASH_ON_MS              120   // value: [20 - 2000]
#define FLASH_OFF_MS             120   // value: [20 - 2000]

#define BOOT_BLUE_MS             800   // Bleu au boot   value: [0 - 10000]
#define BOOT_VU_SPEED_PERCENT    75    // Animation VU boot   value: [5 - 100]

// ═══════════════════════════════════════════════════════════════
//  MODE STANDARD — VU adouci, sans flash (MODE_LENT)
//  Mêmes idées que Flash, valeurs plus calmes (préfixe LENT_).
// ═══════════════════════════════════════════════════════════════
#define LENT_MAX_BRIGHTNESS          50    // Luminosité app (mode Standard)
#define LENT_ATTACK_PERCENT          8     // Montée barre app (mode Standard)
#define LENT_AVG_SMOOTH_PERCENT      35
#define LENT_PEAK_SMOOTH_PERCENT     50
#define LENT_DESCENT_DELAY_SEC       6
#define LENT_DESCENT_DURATION_SEC    60
#define LENT_BOOT_BLUE_MS            0     // 0 = pas de bleu au boot
#define LENT_BOOT_VU_SPEED_PERCENT   20

// ═══════════════════════════════════════════════════════════════
//  MÉDITATION GUIDÉE — séances 2 / 5 / 10 min (réglé dans l'app, pas ici)
// ═══════════════════════════════════════════════════════════════
#define MEDIT_COUNTDOWN_SEC      5
#define MEDIT_DUR_2MIN_SEC       120
#define MEDIT_DUR_5MIN_SEC       300
#define MEDIT_DUR_10MIN_SEC      600
// Profil 2 min
#define MEDIT_P0_INSPIRE_SEC     4
#define MEDIT_P0_HOLD_SEC        2
#define MEDIT_P0_EXPIRE_SEC      5
#define MEDIT_P0_HOLD_EMPTY_SEC  2
#define MEDIT_P0_PAUSE_SEC       1
// Profil 5 min
#define MEDIT_P1_INSPIRE_SEC     5
#define MEDIT_P1_HOLD_SEC        3
#define MEDIT_P1_EXPIRE_SEC      6
#define MEDIT_P1_HOLD_EMPTY_SEC  2
#define MEDIT_P1_PAUSE_SEC       1
// Profil 10 min
#define MEDIT_P2_INSPIRE_SEC     6
#define MEDIT_P2_HOLD_SEC        4
#define MEDIT_P2_EXPIRE_SEC      7
#define MEDIT_P2_HOLD_EMPTY_SEC  3
#define MEDIT_P2_PAUSE_SEC       2
// Couleurs respiration (GRB)
#define MEDIT_COLOR_IN_R         0
#define MEDIT_COLOR_IN_G         200
#define MEDIT_COLOR_IN_B         255
#define MEDIT_COLOR_HOLD_R       255
#define MEDIT_COLOR_HOLD_G       160
#define MEDIT_COLOR_HOLD_B       0
#define MEDIT_COLOR_OUT_R        255
#define MEDIT_COLOR_OUT_G        0
#define MEDIT_COLOR_OUT_B        180
#define MEDIT_COLOR_EMPTY_R      220
#define MEDIT_COLOR_EMPTY_G      220
#define MEDIT_COLOR_EMPTY_B      255
#define MEDIT_COLOR_DONE_R       0
#define MEDIT_COLOR_DONE_G       180
#define MEDIT_COLOR_DONE_B       80

// ═══════════════════════════════════════════════════════════════
//  WI-FI — réseau Cantaluz (téléphone)
// ═══════════════════════════════════════════════════════════════
#define WIFI_ENABLE            1
#define WIFI_OPEN_NETWORK      0
#define WIFI_AP_SSID           "Cantaluz"
#define WIFI_AP_PASS           "cantaluz1"
#define WIFI_AP_CHANNEL        6     // value: [1 - 13]
#define WIFI_HTTP_PORT         80
#define WIFI_MDNS_NAME         "cantaluz"
#define WIFI_CAPTIVE_PORTAL    1

// ═══════════════════════════════════════════════════════════════
//  DEBUG — garder commenté avec Wi-Fi / usage téléphone
// ═══════════════════════════════════════════════════════════════
//#define DEBUG_SERIAL
#define SERIAL_BAUD            115200
#define DEBUG_INTERVAL_MS      5000
#define LOOP_MIN_PERIOD_MS     25
