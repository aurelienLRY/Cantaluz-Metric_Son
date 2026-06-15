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
| **Méditation guidée** | `MODE_MEDITATION` (2) | `ModeMeditation.cpp` | Respiration guidée ; micro ignoré pendant la séance |
| **Défi Fifou** | `MODE_DEFI_FIFOU` (3) | `ModeDefiFifou.cpp` | Jeu du calme ; gain en zone verte, statu quo orange, perte rouge |

- **Au boot** : le mode initial est **`MODE_ACTIF`** dans `Config.h`.
- **En cours d’exécution** : l’app web change `g.live.activeMode` (`Modes.cpp` → `modesSetActive()`).
- **Après redémarrage** : retour aux valeurs de `Config.h` (pas de sauvegarde en mémoire flash).

## App web (si `WIFI_ENABLE == 1`)

| Onglet | Contenu |
|--------|---------|
| **Dashboard** | Graphique ambiance 30 s, barre VU, modes Flash / Standard / Méditation / Défi Fifou |
| **Méditation guidée** | Durée 2 / 5 / 10 min, Démarrer, compte à rebours, chrono, phases |
| **Défi Fifou** | Durée 2 / 5 / 10 min, Démarrer, compte à rebours, chrono, LED gagnées / objectif |
| **Réglages** | Zone calme, zone animée, luminosité, montée barre (grisés en méditation et Défi Fifou) |

| Route API | Rôle |
|-----------|------|
| `GET /api/status` | Niveau sonore, barre, mode, état méditation |
| `GET /api/settings?...&mode=` | Applique config live (`mode` 0 / 1 / 2 / 3) |
| `GET /api/reset?field=...` | Restaure un paramètre depuis `Config.h` |
| `GET /api/meditation/start?dur=120\|300\|600` | Compte à rebours puis séance |
| `GET /api/meditation/stop` | Arrête la séance |
| `GET /api/fifou/start?dur=120\|300\|600` | Compte à rebours puis défi |
| `GET /api/fifou/stop` | Arrête le défi |

Réglages live : `activeMode`, seuils vert/orange, luminosité, montée barre, **sensibilité** (`sensitivity` 0–100).

## Rappel du principe (mode Flash)

1. **Hauteur** : LED allumées depuis le DIN selon le volume (`displayLevel`).
2. **Couleur** : selon la position sur le ruban (plages `ADC_FIN_ZONE_*`).
3. **Flash bleu** : à la montée vert → orange → rouge (pas à la descente).

Le mode **Standard** reprend la même barre VU et les mêmes zones couleur, sans étape flash.

## Mode Standard — paramètres `LENT_*`

Utilisés quand le mode **Standard** est actif (`MODE_LENT` / app web) :  
`LENT_ATTACK_PERCENT`, `LENT_DESCENT_DURATION_SEC`, `LENT_MAX_BRIGHTNESS`, `LENT_BOOT_BLUE_MS` (0 = pas de bleu au boot), etc.

## Config.h — une seule source, pas de doublons inutiles

| Où | Quoi |
|----|------|
| **App Réglages** | Sensibilité, Zone calme, Zone animée, Luminosité, Montée barre (live, jusqu’au reboot) |
| **Config.h** | Défauts au boot, matériel, méditation, Wi-Fi, comportement Flash vs Standard |

### Pourquoi `ATTACK_*` et `LENT_ATTACK_*` ?

Ce ne sont **pas** la même chose en double :

| Paramètre Flash | Paramètre Standard | Rôle |
|-----------------|-------------------|------|
| `ATTACK_PERCENT` | `LENT_ATTACK_PERCENT` | Vitesse montée barre |
| `MAX_BRIGHTNESS` | `LENT_MAX_BRIGHTNESS` | Luminosité |
| `AVG_SMOOTH_PERCENT` | `LENT_AVG_SMOOTH_PERCENT` | Stabilité barre |
| `PEAK_SMOOTH_PERCENT` | `LENT_PEAK_SMOOTH_PERCENT` | Lissage (Flash seulement pour paliers) |
| `DESCENT_*` | `LENT_DESCENT_*` | Descente barre |

Le mode actif choisit **un** jeu à la fois (`configApply` ou `configApplyLent`).

### Sensibilité vs Zone calme / animée

| Curseur app | Effet |
|-------------|--------|
| **Sensibilité** | Porte de bruit + hauteur de barre (voir `MIC_SENS_*` ci-dessous) |
| **Zone calme / animée** | Seuils **eff** pour flashs et répartition vert / orange / rouge sur le ruban (`ADC_FIN_ZONE_*`) |

### Paramètres `MIC_SENS_*` (Config.h)

Le curseur **Sensibilité** de l’app (0–100) ne se règle pas directement dans `Config.h` :  
`DEFAULT_SENSITIVITY` fixe seulement la **valeur au boot**.  
Les six constantes `MIC_SENS_*` définissent **comment** le curseur est converti en trois nombres utilisés par `MicSensor.cpp` :

| Constante | Rôle | Si sensibilité = **0** (faible) | Si sensibilité = **100** (forte) |
|-----------|------|--------------------------------|----------------------------------|
| `MIC_SENS_GATE_MIN` / `MAX` | **Porte** : soustraite au `raw` pour obtenir `eff` | gate = **110** (beaucoup filtré) | gate = **10** (peu filtré) |
| `MIC_SENS_SPAN_MIN` / `MAX` | **Plage** : `eff` needed pour barre à 100 % | span = **720** (faut parler fort) | span = **220** (barre monte vite) |
| `MIC_SENS_DB_MIN` / `MAX` | **Zone morte** : en dessous, la barre ne monte pas | deadband = **35** (très stable) | deadband = **8** (plus nerveux) |

Formules (`s` = sensibilité 0–100) :

```
micGate     = MIC_SENS_GATE_MAX - s × (GATE_MAX - GATE_MIN) / 100
micSpan     = MIC_SENS_SPAN_MAX - s × (SPAN_MAX - SPAN_MIN) / 100
micDeadband = MIC_SENS_DB_MAX   - s × (DB_MAX   - DB_MIN)   / 100

eff = max(0, raw - micGate)
hauteur barre ≈ eff / micSpan   (0 % … 100 %)
```

**Exemple** avec défaut `DEFAULT_SENSITIVITY = 8` → gate ≈ 102, span ≈ 680 :

- Pièce calme, `raw = 25` → `eff = 0` → barre au minimum (quelques LED vertes).
- Voix normale, `raw = 180` → `eff = 78` → barre ≈ 11 %.
- Cri / forte voix, `raw = 400` → `eff = 298` → barre ≈ 44 %.

Pour une salle bruyante : baisser la sensibilité dans l’app (0–10) ou augmenter `MIC_SENS_GATE_MAX`.  
Pour une salle très calme où la voix ne monte pas assez : monter la sensibilité ou diminuer `MIC_SENS_SPAN_MAX`.

## Mode Défi Fifou — paramètres `FIFOU_*`

Utilisés quand le mode **Défi Fifou** est actif (`MODE_DEFI_FIFOU` / app web) :

| Paramètre | Rôle |
|-----------|------|
| `FIFOU_START_LEDS` | Nombre de LED au départ (défaut 20) |
| `FIFOU_CALM_RATIO_NUM` / `DEN` | Temps calme minimum pour gagner (ex. 80/120 → 1 min 20 sur 2 min) |
| `FIFOU_LOSS_GAIN_PERCENT` | Perte en rouge = % de la vitesse de gain (défaut 40 %, plus lent) |
| `FIFOU_COLOR_*` | Couleur cyan du jeu (uniforme sur le bandeau) |
| `FIFOU_WIN_FIREWORKS_MS` | Durée du feu d'artifice en cas de victoire |
| `FIFOU_COUNTDOWN_SEC` | Compte à rebours avant le défi (5 s) |

Les seuils **Zone calme / animée** de l'app déterminent quand on gagne, stagne ou perd (même plages et hystérésis que les modes Flash / Standard : `ledStateWithHysteresis`, `ADC_FIN_ZONE_*`).

## Sections Config.h (résumé)

## Ajouter un mode plus tard

1. `BruitLedMode` dans `Types.h`
2. `ModeXxx.cpp` + `ModeXxx.h`
3. Branches dans `Modes.cpp`
4. `MODE_ACTIF` dans `Config.h`

## Debug

Activer `#define DEBUG_SERIAL` dans `Config.h` — moniteur **115200** baud.
