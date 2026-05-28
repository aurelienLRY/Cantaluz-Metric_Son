# Cantaluz

**La lumière qui répond au son** — projet pédagogique pour une école occitane.

Cantaluz transforme la voix, la musique et le bruit ambiant en une barre lumineuse vivante : un ruban LED qui monte avec le volume et change de palier — vert, orange, rouge — avec des flashs bleus à chaque montée d’intensité. Le nom vient de l’occitan *canta* (chanter) et *luz* (lumière).

---

## Aperçu

| | |
|---|---|
| **Carte** | WeMos D1 mini / ESP8266 |
| **Micro** | MAX4466 (GY) sur **A0** |
| **LED** | Ruban WS2812B sur **D2** (GPIO4) |
| **Mode actuel** | Immédiat — VU réactif + zones couleur + flash bleu |
| **Réglages** | `Main/Config.h` |

```
[DIN]  ████████░░░░░░░░░░░░░░░░░░░░░░  → fin du ruban
       vert    orange      rouge
       ↑ hauteur = niveau sonore
       ↑ couleur = position sur le ruban (plages ADC)
```

---

## Matériel

- WeMos D1 R2 & mini (ou ESP8266 équivalent, CH340G)
- Module micro **MAX4466** → broche **A0**
- Ruban **WS2812B** 5 V (ex. 60 LED/m × 5 m = 300 LED)
  - Données : **D2** + résistance **470 Ω** en série
  - Alimentation **5 V externe** obligatoire pour le ruban
  - **GND commun** entre carte et alim ruban
- Bibliothèque Arduino : [FastLED](https://github.com/FastLED/FastLED)

> Ruban de test (17 LED) : dans `Config.h`, remplacer `LED_COUNT` par `17`.

---

## Installation rapide

1. Cloner le dépôt et ouvrir le dossier **`Main`** dans l’IDE Arduino (sketch `Main.ino`).
2. Installer **FastLED** (Gestionnaire de bibliothèques).
3. Carte : **LOLIN(WEMOS) D1 R2 & mini** (ou Generic ESP8266).
4. Ajuster `Config.h` (nombre de LED, seuils, luminosité).
5. Téléverser **`Main.ino`**.
6. (Optionnel) Moniteur série **115200** baud si `DEBUG_SERIAL` est actif.

---

## Configuration

Tous les paramètres utilisateur sont dans **`Main/Config.h`**, documentés ainsi :

```cpp
#define TRANSITION_COOLDOWN_SEC 3  // Permet d'espacer deux séries de flashs…   value: [0 - 10]
```

| Document | Contenu |
|----------|---------|
| [PARAMETRES.md](PARAMETRES.md) | Rappel des sections et du mode immédiat |
| [FICHIERS.md](FICHIERS.md) | Architecture du code, flux boot / boucle |

**Ne pas modifier** le code des modules pour un simple réglage : tout passe par `Config.h`.

---

## Structure du projet

```
Cantaluz/
└── Main/                     ← dossier sketch Arduino (nom = Main.ino)
    ├── README.md             ← ce fichier
    ├── Main.ino              ← point d'entrée (setup / loop)
    ├── Config.h              ← réglages
    ├── Types.h
    ├── ModeImmediat.*        ← comportement actuel
    ├── MicSensor.*           ← micro + barre VU
    ├── LedStrip.*            ← ruban WS2812B
    ├── FlashEtat.*           ← flashs bleus
    └── …
```

---

## Comportement (mode immédiat)

1. **Boot** — ruban bleu, animation VU verte, calibration du silence.
2. **En fonctionnement** — la barre monte vite avec le son ; elle redescend après quelques secondes sous la moyenne.
3. **Paliers** — passage vert → orange → rouge déclenche des **flashs bleus** (un cran à la fois, pas à la descente).
4. **Couleurs sur le ruban** — réparties selon les plages ADC (`ADC_FIN_ZONE_VERT`, `ADC_FIN_ZONE_ORANGE`), pas selon le volume instantané de chaque LED.

D’autres modes « LED vs bruit » pourront être ajoutés via `Modes.cpp` et `MODE_ACTIF` dans `Config.h`.

---

## Règles de participation

Ce dépôt est un projet **collectif d’école**. Pour garder l’historique liside et les revues simples, chaque contribution suit le modèle **une branche → une pull request**.

### Principe : une branche, une PR, un sujet

| Règle | Détail |
|-------|--------|
| **Une branche = un seul objectif** | Une fonctionnalité, un correctif ou une amélioration documentée — pas plusieurs sujets mélangés. |
| **Une PR = une branche** | Chaque pull request pointe vers **une seule** branche dédiée. Pas de PR « fourre-tout ». |
| **Branche unique par contributeur et par sujet** | Si le sujet change, créer une **nouvelle** branche depuis `main` (ou `master`), ne pas empiler des commits sans lien sur la même branche. |
| **Nom de branche explicite** | Ex. `feat/calibration-silence`, `fix/flash-rebond`, `docs/readme-occitan`. |
| **Base à jour** | Avant d’ouvrir la PR, mettre sa branche à jour avec la branche principale (`git pull --rebase origin main`). |
| **Config.h pour les réglages** | Les seuils et délais se règlent dans `Config.h` ; le code métier reste modulaire. |
| **Pas de secrets** | Ne jamais committer mots de passe, clés Wi-Fi, fichiers `.env`, etc. |

### Workflow recommandé

```bash
git checkout main
git pull origin main
git checkout -b feat/mon-sujet-clair

# … modifications, tests sur la carte …

git add .
git commit -m "feat: description courte en français"
git push -u origin feat/mon-sujet-clair
```

Ouvrir ensuite **une** pull request : `feat/mon-sujet-clair` → `main`.

### Contenu attendu dans une PR

- **Titre** clair (ex. « Ajout du mode lent pour la descente de barre »).
- **Description** : objectif, tests réalisés sur le matériel (WeMos + ruban + micro).
- **Périmètre limité** : si la PR dépasse ~300 lignes ou touche plusieurs modules sans lien, la scinder.
- **Revue** : au moins un pair de l’équipe valide avant fusion.

### Ce qui sera refusé

- PR regroupant plusieurs fonctionnalités non liées.
- Branche réutilisée pour un second sujet après merge (repartir de `main`).
- Modifications massives de formatage seules, sans but pédagogique.
- Commit direct sur `main` (sauf maintenance par les responsables du dépôt).

### Responsables

Les mainteneurs du dépôt (enseignants ou référents élèves) valident les fusions et peuvent demander des changements sur la branche avant merge.

---

## Crédits et contexte

Projet développé dans le cadre d’une **école occitane** : faire dialoguer langue, son et lumière.  
Cantaluz — *canta* + *luz* — incarne l’idée que la voix de l’école peut illuminer l’espace.

---

## Licence

À définir par l’établissement (souvent MIT ou licence libre pour un projet pédagogique). Préciser ici la licence choisie lors de la publication du dépôt.
