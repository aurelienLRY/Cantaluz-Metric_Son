# Paramètres — Cantaluz (Main.ino)

> Réglages détaillés avec plages : voir **`Config.h`** (format `// Permet de… value: [min - max]`).  
> Rôle de chaque fichier : voir **`FICHIERS.md`**.

## Fichiers à ouvrir selon le besoin

| Objectif | Fichier |
|----------|---------|
| Changer un seuil, un délai, le nombre de LED | `Config.h` |
| Comprendre vert / orange / rouge dans le code | `Types.h` |
| Voir l’architecture du projet | `FICHIERS.md` |

## Mode actif

- **`MODE_ACTIF`** = `MODE_IMMEDIAT` dans `Config.h`
- Implémentation : `ModeImmediat.cpp`

## Rappel du principe (mode immédiat)

1. **Hauteur** : LED allumées depuis le DIN selon le volume (`displayLevel`).
2. **Couleur** : selon la position sur le ruban (plages `ADC_FIN_ZONE_*`).
3. **Flash bleu** : à la montée vert → orange → rouge (pas à la descente).

## Sections Config.h

| Section | Exemples |
|---------|----------|
| Bandeau | `LED_COUNT`, `MAX_BRIGHTNESS`, `LED_PIN` |
| Micro | `SAMPLE_COUNT`, `PEAK_SMOOTH_PERCENT` |
| Plages ADC | `ADC_FIN_ZONE_VERT`, `ADC_FIN_ZONE_ORANGE` |
| Hauteur VU | `MIN_LEDS_ON`, `USE_AUTO_VU_MAX`, `CAL_VU_MARGIN` |
| Montée / descente | `ATTACK_PERCENT`, `DESCENT_DELAY_SEC`, `DESCENT_DURATION_SEC` |
| Flash bleu | `TRANSITION_COOLDOWN_SEC`, `FLASH_COUNT`, `STATE_HOLD_MS` |
| Boot | `BOOT_BLUE_MS`, `BOOT_VU_SPEED_PERCENT` |
| Debug | `DEBUG_SERIAL`, `SERIAL_BAUD`, `DEBUG_INTERVAL_MS` |

## Ajouter un mode plus tard

1. `BruitLedMode` dans `Types.h`
2. `ModeXxx.cpp` + `ModeXxx.h`
3. Branches dans `Modes.cpp`
4. `MODE_ACTIF` dans `Config.h`

## Debug

Activer `#define DEBUG_SERIAL` dans `Config.h` — moniteur **115200** baud.
