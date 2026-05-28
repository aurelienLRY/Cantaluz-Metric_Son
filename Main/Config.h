#pragma once
/*
 * Config.h — Paramètres utilisateur (modifier ici)
 *
 * Format :  // Permet de …   value: [min - max]
 * MODE_ACTIF : voir Modes.h pour ajouter d'autres comportements LED vs bruit.
 */

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════
//  MODE DE GESTION LED vs BRUIT
// ═══════════════════════════════════════════════════════════════
#define MODE_IMMEDIAT  0   // Identifiant mode immédiat (ne pas changer)
#define MODE_ACTIF     MODE_IMMEDIAT  // Permet de choisir le comportement actif   value: [MODE_IMMEDIAT]

// ═══════════════════════════════════════════════════════════════
//  BANDEAU WS2812B
// ═══════════════════════════════════════════════════════════════
#define LEDS_PER_METER    60    // Permet de définir la densité LED par mètre du ruban   value: [1 - 144]
#define STRIP_LENGTH_M    5     // Permet de calculer LED_COUNT = densité × longueur (m)   value: [1 - 10]
#define LED_COUNT         (LEDS_PER_METER * STRIP_LENGTH_M)  // Nombre total LED ; ruban test : remplacer par 17   value: [1 - 600]
#define LED_PIN           4     // Permet de brancher les données sur ce GPIO (D2 = 4 sur WeMos D1)   value: [0 - 16]
#define MAX_BRIGHTNESS    80    // Permet de limiter la luminosité globale (économie + yeux)   value: [0 - 255]

// ═══════════════════════════════════════════════════════════════
//  MICRO MAX4466 (entrée A0, peak typique 0-1023)
// ═══════════════════════════════════════════════════════════════
#define MIC_PIN             A0  // Permet de lire le micro sur la broche analogique   value: [A0]
#define SAMPLE_COUNT        64  // Permet de lisser le peak sur N lectures par boucle   value: [8 - 256]
#define SAMPLE_DELAY_US     200 // Permet d'espacer chaque lecture analogique (µs)   value: [50 - 1000]
#define PEAK_SMOOTH_PERCENT 15  // Permet de lisser le peak pour les flashs (évite micro-coupures)   value: [0 - 100]

// ═══════════════════════════════════════════════════════════════
//  PLAGES ADC → couleurs sur le ruban + seuils flash bleu
//  (mêmes bornes pour répartition LED et montée vert → orange → rouge)
// ═══════════════════════════════════════════════════════════════
#define ADC_PLAGE_MIN       0     // Permet de fixer la borne basse utile du peak   value: [0 - 1022]
#define ADC_PLAGE_MAX       1023  // Permet de fixer la borne haute utile du peak   value: [1 - 1023]
#define ADC_FIN_ZONE_VERT   500   // Permet de délimiter la zone VERTE (peak ≤ cette valeur)   value: [0 - 1022]
#define ADC_FIN_ZONE_ORANGE 800   // Permet de délimiter la zone ORANGE (peak ≤ cette valeur)   value: [ADC_FIN_ZONE_VERT+1 - 1023]
#define ADC_HYST_VERT       80    // Permet d'éviter le rebond en redescendant depuis orange/rouge vers vert   value: [0 - 500]
#define ADC_HYST_ORANGE     80    // Permet d'éviter le rebond en redescendant depuis rouge vers orange   value: [0 - 500]

// ═══════════════════════════════════════════════════════════════
//  HAUTEUR DE LA BARRE VU (nombre de LED allumées)
// ═══════════════════════════════════════════════════════════════
#define MIN_LEDS_ON         5     // Permet d'avoir toujours au moins N LED allumées (bruit de fond visible)   value: [1 - 50]
#define ADC_VU_MIN          5     // Permet de traiter les peak en dessous comme silence (barre au minimum)   value: [0 - 100]
#define USE_AUTO_VU_MAX     1     // Permet de calibrer automatiquement la barre pleine au boot (1=oui, 0=non)   value: [0 - 1]
#define CALIBRATE_MS        2500UL // Permet de régler la durée d'écoute du silence au boot (ms)   value: [500 - 30000]
#define CAL_VU_MARGIN       200   // Permet d'ajouter une marge au bruit de fond pour définir « barre pleine »   value: [50 - 500]
#define MANUAL_VU_MAX       0     // Permet de forcer le peak « barre pleine » ; 0 = utilise la calibration auto   value: [0 - 1023]

// ═══════════════════════════════════════════════════════════════
//  MONTÉE / DESCENTE DE LA BARRE (réglages en % ou secondes)
// ═══════════════════════════════════════════════════════════════
#define ATTACK_PERCENT          45  // Permet de régler la rapidité de montée de la barre (100 = quasi instantané)   value: [0 - 100]
#define AVG_SMOOTH_PERCENT      8   // Permet de lisser la moyenne du peak (déclenche la descente)   value: [0 - 100]
#define DESCENT_DELAY_SEC       5   // Permet d'attendre N secondes sous la moyenne avant que la barre redescende   value: [0 - 120]
#define DESCENT_DURATION_SEC    67  // Permet de vider la barre en N secondes après ce délai   value: [1 - 600]

// ═══════════════════════════════════════════════════════════════
//  FLASH BLEU (montée d'état vert → orange → rouge, un cran à la fois)
// ═══════════════════════════════════════════════════════════════
#define STATE_HOLD_MS           200 // Permet d'exiger un maintien au-dessus du seuil avant de lancer un flash (ms)   value: [0 - 5000]
#define FLASH_HOLD_RESET_MS     400 // Permet d'ignorer les micro-coupures sous le seuil sans reset du timer flash   value: [0 - 5000]
#define TRANSITION_COOLDOWN_SEC 3   // Permet d'espacer deux séries de flashs bleus (secondes)   value: [0 - 10]
#define FLASH_COUNT             3   // Permet de choisir le nombre de flashs bleus par montée d'état   value: [1 - 20]
#define FLASH_ON_MS             120 // Permet de régler la durée d'allumage bleu de chaque impulsion (ms)   value: [20 - 2000]
#define FLASH_OFF_MS            120 // Permet de régler la durée d'extinction entre deux impulsions (ms)   value: [20 - 2000]

// ═══════════════════════════════════════════════════════════════
//  BOOT (séquence au démarrage)
// ═══════════════════════════════════════════════════════════════
#define BOOT_BLUE_MS            800 // Permet d'afficher le ruban entièrement bleu juste après l'init (ms)   value: [0 - 10000]
#define BOOT_VU_SPEED_PERCENT   75  // Permet de régler la vitesse de l'animation VU verte au boot (100=rapide)   value: [5 - 100]

// ═══════════════════════════════════════════════════════════════
//  DEBUG SÉRIE (moniteur Arduino)
// ═══════════════════════════════════════════════════════════════
#define DEBUG_SERIAL                  // Permet d'activer les logs ; commenter la ligne pour désactiver
#define SERIAL_BAUD             115200 // Permet de régler la vitesse du port série   value: [9600 - 921600]
#define DEBUG_INTERVAL_MS       400   // Permet d'espacer les lignes de debug (ms)   value: [100 - 10000]
