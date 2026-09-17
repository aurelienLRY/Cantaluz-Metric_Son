# Cantaluz

**La lumière qui répond au son** — projet pédagogique pour une école occitane.

Cantaluz transforme la voix, la musique et le bruit ambiant en une barre lumineuse vivante : un ruban LED qui monte avec le volume et change de palier — vert, orange, rouge — avec des flashs bleus à chaque montée d’intensité. Le nom vient de l’occitan *canta* (chanter) et *luz* (lumière).

Cette branche cible exclusivement l’**ESP32-WROOM-32U** (antenne externe U.FL).

---

## Aperçu

| | |
|---|---|
| **Carte** | ESP32-WROOM-32U (DevKit / module à antenne **U.FL**) |
| **Micro** | MAX4466 (GY) sur **GPIO34** (ADC1), alim **3,3 V** |
| **LED** | Ruban WS2812B sur **GPIO4** |
| **Modes** | **Flash**, **Standard**, **Méditation guidée**, **Défi Fifou** (jeu du calme) |
| **Réglages** | `Main/Config.h` au boot ; sensibilité et seuils aussi via l’app web (jusqu’au redémarrage) |
| **Wi-Fi** | `Cantaluz` / `cantaluz1` → `http://cantaluz.local` ou `192.168.4.1` (portail captif) |

```
[DIN]  ████████░░░░░░░░░░░░░░░░░░░░░░  → fin du ruban
       vert    orange      rouge
       ↑ hauteur = niveau sonore
       ↑ couleur = position sur le ruban (plages ADC)
```

---

## Matériel

- Carte **ESP32-WROOM-32U** (antenne **U.FL** fournie à brancher)
- Module micro **MAX4466** → **GPIO34**, VCC en **3,3 V** (pas 5 V)
- Ruban **WS2812B** 5 V (ex. 60 LED/m × 5 m)
  - Données : **GPIO4** + résistance **470 Ω** en série
  - Alimentation **5 V externe** obligatoire pour le ruban
  - **GND commun** entre carte et alim ruban
- Bibliothèque Arduino : [FastLED](https://github.com/FastLED/FastLED)

> Ruban de test (17 LED) : dans `Config.h`, remplacer `LED_COUNT` par `17`.

---

## 1. Logiciel à installer (pour injecter le programme)

Tu n’as **pas** besoin d’esptool en ligne de commande. Un seul logiciel suffit pour compiler et envoyer le firmware :

### Étape A — Arduino IDE 2

1. Télécharger et installer **[Arduino IDE 2](https://www.arduino.cc/en/software)** (Windows).
2. Lancer l’IDE.

### Étape B — Support ESP32 (core Espressif)

1. Menu **Fichier → Préférences**.
2. Dans **URL de gestionnaire de cartes supplémentaires**, coller :

   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

3. Valider.
4. Menu **Outils → Type de carte → Gestionnaire de cartes…**
5. Chercher **esp32** et installer **esp32 by Espressif Systems** (dernière version stable).

### Étape C — Bibliothèque FastLED

1. Menu **Outils → Gérer les bibliothèques…**
2. Chercher **FastLED** → **Installer**.

### Étape D — Pilote USB (si aucun port COM)

1. Brancher la carte en USB.
2. Si **Outils → Port** est vide : regarder le chip près de l’USB sur la carte.
   - **CH340** → installer le [pilote CH340](http://www.wch-ic.com/downloads/CH341SER_EXE.html)
   - **CP2102** → installer le [pilote Silicon Labs CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
3. Débrancher / rebrancher, puis choisir le port **COMx** dans l’IDE.

---

## 2. Câblage

**Brancher l’antenne U.FL** sur le connecteur du module avant tout test Wi‑Fi (sinon le SoftAP peut échouer ou être très faible).

| Élément | Broche ESP32 | Notes |
|---------|--------------|--------|
| MAX4466 **OUT** | **GPIO34** | Entrée analogique ADC1 |
| MAX4466 **VCC** | **3V3** | Ne pas alimenter le micro en 5 V |
| MAX4466 **GND** | **GND** | GND commun |
| WS2812 **DIN** | **GPIO4** | Résistance **470 Ω** en série sur DIN |
| WS2812 **5 V** | Alim **5 V externe** | Pas l’USB seul pour un long ruban |
| WS2812 **GND** | **GND** | GND commun carte + alim ruban |
| Antenne | Connecteur **U.FL** | Obligatoire dès que le Wi‑Fi tourne |

Schéma rapide :

```
MAX4466 OUT ────── GPIO34
MAX4466 VCC ────── 3V3
MAX4466 GND ────── GND

WS2812 DIN ──[470 Ω]── GPIO4
WS2812 5V  ─────────── alim 5 V externe (+)
WS2812 GND ─────────── GND (commun avec la carte)

Antenne U.FL ──────── connecteur antenne du module
USB PC ─────────────── port USB de la carte (programmation + 3,3 V logique)
```

À éviter :

- GPIO **6 à 11** (flash interne de l’ESP32)
- Tirer fort GPIO **0 / 2 / 12 / 15** au démarrage (broches de boot)

---

## 3. Téléverser (injecter le firmware)

1. Brancher l’USB, antenne U.FL en place.
2. Dans Arduino IDE : **Fichier → Ouvrir…** → ouvrir le dossier **`Main`** (fichier `Main.ino`).
3. Menu **Outils → Carte → ESP32 Arduino → ESP32 Dev Module**.
4. Réglages recommandés (**Outils**) :

   | Option | Valeur recommandée |
   |--------|-------------------|
   | Board | **ESP32 Dev Module** |
   | Flash Size | **4MB (32Mb)** |
   | Partition Scheme | **Default 4MB with spiffs** |
   | CPU Frequency | **240 MHz** |
   | Upload Speed | **921600** (ou **115200** si erreur) |
   | Port | **COMx** de votre câble USB |

5. Ajuster si besoin `Main/Config.h` (nombre de LED, seuils, luminosité).
6. Fermer le moniteur série s’il est ouvert, puis cliquer **Téléverser** (flèche →).
7. Si le message **Failed to connect** apparaît :
   - Maintenir le bouton **BOOT** (parfois nommé **IO0**)
   - Relancer **Téléverser**
   - Relâcher **BOOT** dès que l’IDE affiche l’écriture en flash
8. (Optionnel) Moniteur série **115200** baud si `DEBUG_SERIAL` est actif dans `Config.h`.

### Vérifier que ça marche

1. Sur le téléphone : se connecter au Wi‑Fi **`Cantaluz`** (mot de passe : `cantaluz1`).
2. Ouvrir Chrome sur `http://cantaluz.local` ou `http://192.168.4.1`.
3. L’app affiche le dashboard (VU, modes Flash / Standard / Méditation / Défi Fifou) et les réglages.

Si le réseau n’apparaît pas :

1. Vérifier que l’**antenne U.FL** est bien enclenchée.
2. Carte IDE = **ESP32 Dev Module** (pas une variante ESP8266).
3. Moniteur série 115200 : chercher `SoftAP: OK` et `IP: http://192.168.4.1`.
4. Sur Android / iPhone : désactiver *« Passer automatiquement aux données mobiles »* / avertissement *« Réseau sans Internet »*.
5. Tester aussi depuis un PC portable.
6. Essayer un autre canal `WIFI_AP_CHANNEL` dans `Config.h` (`1` ou `11`).
7. Utiliser un câble USB **données** (pas charge seule) et une alim correcte.

---

## App téléphone (rappel)

Si `WIFI_ENABLE` est à `1` dans `Config.h` :

- Slogan : *« Outil d’accompagnement au calme. »*
- **Dashboard** : graphique d’ambiance (30 s), barre VU, modes **Flash**, **Standard**, **Méditation guidée**, **Défi Fifou**.
- **Méditation guidée** : **1 / 2 / 5 min**, compte à rebours 5 s ; rythme CP (~6 ans).
- **Défi Fifou** : jeu du calme ; 20 LED cyan ; victoire = feu d’artifice · défaite = clignotement rouge.
- **Réglages** : sensibilité, zones, luminosité, montée ; **↺** = défauts `Config.h`.
- Au **redémarrage** de la carte, `Config.h` reprend la main.

---

## Configuration

Tous les paramètres utilisateur sont dans **`Main/Config.h`**, documentés ainsi :

```cpp
#define TRANSITION_COOLDOWN_SEC 3  // Permet d'espacer deux séries de flashs…   value: [0 - 10]
```

| Document | Contenu |
|----------|---------|
| [FICHE_UTILISATEUR.md](FICHE_UTILISATEUR.md) | **Fiche A4** — utilisation en classe (modes, app, démarrage) |
| [Main/PARAMETRES.md](Main/PARAMETRES.md) | Quatre modes, app web, sections `Config.h` (dont `FIFOU_*`, `MED_*`) |
| [Main/FICHIERS.md](Main/FICHIERS.md) | Architecture du code, flux boot / boucle / API |

**Ne pas modifier** le code des modules pour un simple réglage : tout passe par `Config.h`.

---

## Structure du projet

```
Cantaluz/
└── Main/                     ← dossier sketch Arduino (nom = Main.ino)
    ├── Main.ino              ← point d'entrée ESP32 (setup / loop)
    ├── Config.h              ← réglages par défaut (boot) + broches GPIO
    ├── AppState.*            ← état global + LiveConfig (web)
    ├── Modes.*               ← dispatch Flash / Standard / Méditation / Défi Fifou
    ├── ModeImmediat.*        ← mode Flash (VU + flash bleu)
    ├── ModeLent.*            ← mode Standard (VU adouci)
    ├── ModeMeditation.*      ← mode Méditation guidée (respiration)
    ├── ModeDefiFifou.*       ← mode Défi Fifou (jeu du calme)
    ├── MicSensor.*           ← micro GPIO34 + barre VU
    ├── LedStrip.*            ← ruban WS2812B sur GPIO4
    ├── FlashEtat.*           ← flashs bleus (mode Flash)
    ├── WifiPortal.*          ← SoftAP ESP32, API, portail captif
    ├── WebAppHtml.h          ← interface mobile (Dashboard / Réglages)
    └── …
```

---

## Comportement des modes

| App (nom affiché) | Firmware | Comportement |
|-------------------|----------|--------------|
| **Flash** | `MODE_IMMEDIAT` | VU réactif ; montée vert → orange → rouge → **flashs bleus** |
| **Standard** | `MODE_LENT` | Vu-mètre fluide selon l’ambiance ; **pas de flash** ; paramètres `LENT_*` |
| **Méditation guidée** | `MODE_MEDITATION` | Séance respiration : **cyan** inspire → **ambre** retiens → **magenta** expire → **lavande** air bloqué ; micro ignoré |
| **Défi Fifou** | `MODE_DEFI_FIFOU` | Jeu du calme : 20 LED **cyan** ; gain en calme / statu quo animé / perte en intense ; victoire = feu d’artifice (~10 s), défaite = clignotement rouge |

Commun aux modes Flash et Standard :

1. **Boot** — ruban bleu, animation VU verte (sans attente silence).
2. **Barre VU** — hauteur selon le volume ; descente après quelques secondes sous la moyenne.
3. **Couleurs sur le ruban** — réparties selon les plages ADC (`ADC_FIN_ZONE_VERT`, `ADC_FIN_ZONE_ORANGE`).

Le mode au **démarrage** est `MODE_ACTIF` dans `Config.h` ; l’app web peut le changer à chaud via `Modes.cpp`.

---

## Règles de participation

Ce dépôt est un projet **collectif d’école**. Pour garder l’historique lisible et les revues simples, chaque contribution suit le modèle **une branche → une pull request**.

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
- **Description** : objectif, tests réalisés sur le matériel (ESP32 + ruban + micro).
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
