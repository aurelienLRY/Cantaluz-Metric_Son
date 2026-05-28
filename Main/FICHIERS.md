# Guide des fichiers — Cantaluz (dossier Main)

## Par où commencer ?

| Besoin | Fichier |
|--------|---------|
| Régler seuils, délais, LED | **Config.h** |
| Comprendre vert/orange/rouge | **Types.h** |
| Ne rien toucher au code | Ouvrir seulement **Config.h** |

---

## Liste des fichiers

### Réglages et types

| Fichier | Rôle | Modifier ? |
|---------|------|------------|
| **Config.h** | Tous les paramètres utilisateur (`// Permet de… value: [min-max]`) | **Oui** — fichier principal |
| **Types.h** | `ColorState`, `MicSample`, liste des modes futurs | Rarement |
| **Convert.h** | % et secondes → valeurs pour le code | Non (sauf nouveau type de réglage) |

### État et conversion

| Fichier | Rôle | Modifier ? |
|---------|------|------------|
| **AppState.h** | Structure `g` : LED, niveaux, minuteurs, états | Non |
| **AppState.cpp** | Variable globale `g`, `configApply()`, `stateName()` | Non |

### Modules fonctionnels

| Fichier | Rôle | Réglages Config.h liés |
|---------|------|-------------------------|
| **MicSensor.h / .cpp** | Lecture micro, barre VU, calibration silence | MICRO, HAUTEUR BARRE VU |
| **LedStrip.h / .cpp** | Ruban, zones couleur, boot visuel | BANDEAU, PLAGES ADC, BOOT |
| **FlashEtat.h / .cpp** | Flashs bleus, paliers montée/descente | FLASH BLEU, PLAGES ADC |
| **DebugLog.h / .cpp** | Moniteur série 115200 | DEBUG SÉRIE |

### Modes

| Fichier | Rôle | Modifier ? |
|---------|------|------------|
| **ModeImmediat.h / .cpp** | Mode immédiat (VU + flash bleu) | Logique mode réactif |
| **ModeLent.h / .cpp** | Mode lent (VU adouci, sans flash) | Logique mode calme |
| **Modes.h / .cpp** | Appelle le mode choisi par `MODE_ACTIF` | Pour ajouter un nouveau mode |
| **Main.ino** | `setup()` / `loop()` Arduino | Presque jamais |

### Documentation

| Fichier | Rôle |
|---------|------|
| **PARAMETRES.md** | Tableau des paramètres (complément de Config.h) |
| **FICHIERS.md** | Ce guide |

---

## Flux au démarrage

```
Main.ino setup()
  → modesSetup()
      → modeImmediatSetup()
          → ledComputeZonesFromPlages()
          → ledInitHardware()
          → ledAfficherBleuComplet()
          → configApply()
          → ledRunBootSequence()
          → micCalibrateVuMax()   (si USE_AUTO_VU_MAX)
```

## Flux à chaque boucle

```
Main.ino loop()
  → modesLoop()
      → modeImmediatLoop()
          → flashUpdateTransition()  (si flash en cours)
          → micSample()
          → micUpdatePeakSmooth()
          → micUpdateDisplayLevel()
          → flashHandleStateMachine()
          → ledRenderVuMeter()
          → debugLogStatusIfDue()
```

---

## Schéma des dépendances

```
Config.h ─────────────────────────────────────────┐
Types.h ─────────────────────────────────────────┤
Convert.h ──► AppState.cpp (configApply)         │
                                                  ▼
                    ┌────────── MicSensor ◄── AppState (g)
                    │                ▲
Modes.cpp ──► ModeImmediat ──┬──► LedStrip ──────┘
                             └──► FlashEtat
                                      ▲
                             DebugLog (optionnel)
```
