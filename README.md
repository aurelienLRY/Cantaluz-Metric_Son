# Cantaluz

**La lumière qui répond au son** — projet pédagogique pour une école occitane.

Cantaluz transforme la voix, la musique et le bruit ambiant en une barre lumineuse vivante : un ruban LED qui monte avec le volume et change de palier — vert, orange, rouge — avec des flashs bleus à chaque montée d’intensité. Le nom vient de l’occitan *canta* (chanter) et *luz* (lumière).

---

## Aperçu

| | |
|---|---|
| **Carte** | WeMos D1 R1 / R2 / mini (ESP8266) |
| **Micro** | MAX4466 (GY) sur **A0** |
| **LED** | Ruban WS2812B sur **D2** (GPIO4) |
| **Modes** | **Flash** (pics → flashs bleus) ou **Standard** (vu-mètre fluide, sans flash) — commutable depuis l’app |
| **Réglages** | `Main/Config.h` au boot ; seuils et luminosité aussi via l’app web (jusqu’au redémarrage) |
| **Wi-Fi** | `Cantaluz` / `cantaluz1` → `http://cantaluz.local` ou `192.168.4.1` (portail captif) |

```
[DIN]  ████████░░░░░░░░░░░░░░░░░░░░░░  → fin du ruban
       vert    orange      rouge
       ↑ hauteur = niveau sonore
       ↑ couleur = position sur le ruban (plages ADC)
```

---

## Matériel

- WeMos **D1 R1**, D1 R2 ou D1 mini (ESP8266, pilote CH340G ou CP2102)
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
3. Carte dans l’IDE : **LOLIN(WEMOS) D1 R1** (votre carte) — *ne pas* utiliser « Generic ESP8266 ».
4. Menu **Outils** (avec D1 R1 sélectionnée) :

   | Option | Valeur recommandée |
   |--------|-------------------|
   | Flash Size | **4MB (FS:2MB OTA:~1019KB)** |
   | CPU Frequency | 80 MHz |
   | Upload Speed | 921600 (ou **115200** si erreur) |
   | Erase Flash | **All Flash Contents** (1× après changement de carte) |
   | Port | COM de votre câble USB |

5. Ajuster `Config.h` (nombre de LED, seuils, luminosité).
6. Téléverser **`Main.ino`** (moniteur série **fermé** pendant l’upload).
7. (Optionnel) Moniteur série **115200** baud si `DEBUG_SERIAL` est actif.
8. **Téléphone** — si `WIFI_ENABLE` est à `1` dans `Config.h` :
   - Se connecter au Wi-Fi **`Cantaluz`** (mot de passe : `cantaluz1`).
   - L’**app** s’ouvre via le portail captif, ou ouvrir **Chrome** sur `http://cantaluz.local` / `192.168.4.1`.
   - Slogan : *« Outil d’accompagnement au calme. »*
   - **Dashboard** : graphique d’ambiance (30 s), barre VU, choix du mode **Flash** ou **Standard**.
   - **Réglages** : zone calme, zone animée, luminosité, montée de la barre ; bouton **↺** = valeur par défaut (`Config.h`) ; **i** = bulle d’aide.
   - Les réglages web s’appliquent tout de suite sur le ruban ; au **redémarrage** de la carte, c’est `Config.h` qui reprend la main.
   - **Ne pas** laisser le moniteur série ouvert en usage normal (sature l’ESP8266).

### Test Wi-Fi matériel (si aucun réseau visible)

1. Ouvrir le dossier **`WifiMinimal`** dans l’IDE Arduino (pas `Main`).
2. Carte : **LOLIN(WEMOS) D1 R1** (la vôtre).
3. **Outils → Effacer la flash : All Flash Contents** (une fois), puis téléverser.
4. Chercher le réseau **`Cantaluz_TEST`** (mot de passe `12345678`).
5. Si **Cantaluz_TEST** n’apparaît pas → problème carte / alim / pilote CH340 / mauvaise carte sélectionnée (pas ESP32).
6. Si **Cantaluz_TEST** apparaît mais pas **Cantaluz** → retéléverser `Main` ; mettre `LED_COUNT` à **17** pour tester (ruban 5 m = beaucoup de RAM).

### Wi-Fi invisible sur le téléphone ?

1. **Carte dans l’IDE** : **LOLIN(WEMOS) D1 R2 & mini** (ESP8266, pas ESP32).
2. **Moniteur série 115200** après téléversement : doit afficher `SoftAP: OK` et `IP: http://192.168.4.1`. Si `ECHEC`, vérifier `WIFI_AP_PASS` (8 caractères minimum) ou laisser vide pour un réseau ouvert.
3. **Android / iPhone** : désactiver *« Passer automatiquement aux données mobiles »* / *« Réseau sans Internet »* — le téléphone cache souvent les AP sans Internet ([voir aussi Random Nerd Tutorials](https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/)).
4. Tester la liste Wi-Fi sur un **PC portable** : le réseau `Cantaluz` y apparaît souvent avant le téléphone.
5. Changer **`WIFI_AP_CHANNEL`** dans `Config.h` (essayer `1` ou `11`).
6. Alimentation **USB correcte** (câble données, pas seulement charge) — le Wi-Fi consomme plus au démarrage.

Référence officielle ESP8266 : [exemple SoftAP](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino).

---

## Configuration

Tous les paramètres utilisateur sont dans **`Main/Config.h`**, documentés ainsi :

```cpp
#define TRANSITION_COOLDOWN_SEC 3  // Permet d'espacer deux séries de flashs…   value: [0 - 10]
```

| Document | Contenu |
|----------|---------|
| [Main/PARAMETRES.md](Main/PARAMETRES.md) | Modes Flash/Standard, app web, sections `Config.h` |
| [Main/FICHIERS.md](Main/FICHIERS.md) | Architecture du code, flux boot / boucle / API |

**Ne pas modifier** le code des modules pour un simple réglage : tout passe par `Config.h`.

---

## Structure du projet

```
Cantaluz/
└── Main/                     ← dossier sketch Arduino (nom = Main.ino)
    ├── Main.ino              ← point d'entrée (setup / loop)
    ├── Config.h              ← réglages par défaut (boot)
    ├── AppState.*            ← état global + LiveConfig (web)
    ├── Modes.*               ← dispatch Flash / Standard
    ├── ModeImmediat.*        ← mode Flash (VU + flash bleu)
    ├── ModeLent.*            ← mode Standard (VU adouci)
    ├── MicSensor.*           ← micro + barre VU
    ├── LedStrip.*            ← ruban WS2812B
    ├── FlashEtat.*           ← flashs bleus (mode Flash)
    ├── WifiPortal.*          ← SoftAP, API, portail captif
    ├── WebAppHtml.h          ← interface mobile (Dashboard / Réglages)
    └── …
WifiMinimal/                  ← test Wi-Fi matériel seul (Cantaluz_TEST)
```

---

## Comportement des modes

| App (nom affiché) | Firmware | Comportement |
|-------------------|----------|--------------|
| **Flash** | `MODE_IMMEDIAT` | VU réactif ; montée vert → orange → rouge → **flashs bleus** |
| **Standard** | `MODE_LENT` | Vu-mètre fluide selon l’ambiance ; **pas de flash** ; paramètres `LENT_*` |

Commun aux deux modes :

1. **Boot** — ruban bleu, animation VU verte, calibration du silence.
2. **Barre VU** — hauteur selon le volume ; descente après quelques secondes sous la moyenne.
3. **Couleurs sur le ruban** — réparties selon les plages ADC (`ADC_FIN_ZONE_VERT`, `ADC_FIN_ZONE_ORANGE`).

Le mode au **démarrage** est `MODE_ACTIF` dans `Config.h` ; l’app web peut le changer à chaud via `Modes.cpp`. D’autres comportements pourront être ajoutés de la même façon.

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
