# Paramètres — Cantaluz (Main.ino)

> Réglages détaillés avec plages : voir **`Config.h`** (format `// Permet de… value: [min - max]`).  
> Rôle de chaque fichier : voir **`FICHIERS.md`**.

## Fichiers à ouvrir selon le besoin

| Objectif | Fichier |
|----------|---------|
| Changer un seuil, un délai, le nombre de LED | `Config.h` |
| Comprendre vert / orange / rouge dans le code | `Types.h` |
| Voir l’architecture du projet | `FICHIERS.md` |

## Modes (Flash / Standard)

| App web | `Config.h` | Fichier | Comportement |
|---------|------------|---------|--------------|
| **Flash** | `MODE_IMMEDIAT` (0) | `ModeImmediat.cpp` | VU réactif + flashs bleus sur les pics |
| **Standard** | `MODE_LENT` (1) | `ModeLent.cpp` | Vu-mètre adouci, **sans flash**, réglages `LENT_*` |

- **Au boot** : le mode initial est **`MODE_ACTIF`** dans `Config.h`.
- **En cours d’exécution** : l’app web change `g.live.activeMode` (`Modes.cpp` → `modesSetActive()`).
- **Après redémarrage** : retour aux valeurs de `Config.h` (pas de sauvegarde en mémoire flash).

## App web (si `WIFI_ENABLE == 1`)

| Onglet | Contenu |
|--------|---------|
| **Dashboard** | Graphique ambiance 30 s, barre VU, boutons Flash / Standard |
| **Réglages** | Zone calme (`ADC_FIN_ZONE_VERT`), zone animée (`ADC_FIN_ZONE_ORANGE`), luminosité, montée barre |

| Route API | Rôle |
|-----------|------|
| `GET /api/status` | Niveau sonore, barre, mode, seuils courants |
| `GET /api/settings?vert=&orange=&bright=&attack=&mode=` | Applique et renvoie la config live |
| `GET /api/reset?field=vert\|orange\|bright\|attack` | Restaure un paramètre depuis `Config.h` |

Réglages live stockés dans **`LiveConfig`** (`AppState.h`) : `activeMode`, `adcFinZoneVert`, `adcFinZoneOrange`, `maxBrightness`, `attackPercent`.

## Rappel du principe (mode Flash)

1. **Hauteur** : LED allumées depuis le DIN selon le volume (`displayLevel`).
2. **Couleur** : selon la position sur le ruban (plages `ADC_FIN_ZONE_*`).
3. **Flash bleu** : à la montée vert → orange → rouge (pas à la descente).

Le mode **Standard** reprend la même barre VU et les mêmes zones couleur, sans étape flash.

## Mode Standard — paramètres `LENT_*`

Utilisés quand le mode **Standard** est actif (`MODE_LENT` / app web) :  
`LENT_ATTACK_PERCENT`, `LENT_DESCENT_DURATION_SEC`, `LENT_MAX_BRIGHTNESS`, `LENT_BOOT_BLUE_MS` (0 = pas de bleu au boot), etc.

## Sections Config.h

| Section | Exemples |
|---------|----------|
| Mode | `MODE_ACTIF`, `MODE_IMMEDIAT`, `MODE_LENT` |
| Bandeau | `LED_COUNT`, `MAX_BRIGHTNESS`, `LED_PIN` |
| Micro | `SAMPLE_COUNT`, `PEAK_SMOOTH_PERCENT` |
| Plages ADC | `ADC_FIN_ZONE_VERT`, `ADC_FIN_ZONE_ORANGE` |
| Hauteur VU | `MIN_LEDS_ON`, `USE_AUTO_VU_MAX`, `CAL_VU_MARGIN` |
| Montée / descente | `ATTACK_PERCENT`, `DESCENT_DELAY_SEC`, `DESCENT_DURATION_SEC` |
| Wi-Fi téléphone | `WIFI_AP_SSID`, `WIFI_MDNS_NAME` (`cantaluz.local`), `WIFI_CAPTIVE_PORTAL` |
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
