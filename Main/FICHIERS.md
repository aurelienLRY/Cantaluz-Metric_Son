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
| **AppState.h** | Structure `g` : LED, niveaux, minuteurs, `LiveConfig` (web) | Non |
| **AppState.cpp** | `g`, `configApply()`, `liveConfigInit()`, `liveResetField()` | Non |

### Modules fonctionnels

| Fichier | Rôle | Réglages Config.h liés |
|---------|------|-------------------------|
| **MicSensor.h / .cpp** | Lecture micro, barre VU, calibration silence | MICRO, HAUTEUR BARRE VU |
| **LedStrip.h / .cpp** | Ruban, zones couleur, boot visuel | BANDEAU, PLAGES ADC, BOOT |
| **FlashEtat.h / .cpp** | Flashs bleus, paliers montée/descente | FLASH BLEU, PLAGES ADC |
| **DebugLog.h / .cpp** | Moniteur série 115200 | DEBUG SÉRIE |
| **WifiPortal.h / .cpp** | SoftAP, mDNS, portail captif, API `/api/*` | WIFI dans Config.h |
| **WebAppHtml.h** | App mobile : Dashboard (graphique, VU, Flash/Standard) + Réglages | Textes UI uniquement |

### Modes

| Fichier | Rôle | Modifier ? |
|---------|------|------------|
| **ModeImmediat.h / .cpp** | Mode **Flash** (VU + flash bleu) | Logique mode réactif |
| **ModeLent.h / .cpp** | Mode **Standard** (VU adouci, sans flash) | Logique mode calme |
| **Modes.h / .cpp** | Dispatch selon `g.live.activeMode` ; `modesSetActive()` | Pour ajouter un nouveau mode |
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
  → wifiPortalLoop()             (si WIFI_ENABLE : DNS + HTTP)
  → modesLoop()
      → modeImmediatLoop()  ou  modeLentLoop()
          → micSample() … ledRenderVuMeter()
          → (Flash uniquement) flashHandleStateMachine()
```

## App web (WifiPortal + WebAppHtml)

```
Téléphone → Wi-Fi Cantaluz
  → portail captif ou http://cantaluz.local
  → WebAppHtml.h (PROGMEM)
  → /api/status | /api/settings | /api/reset
  → g.live (LiveConfig) + modesSetActive()
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
