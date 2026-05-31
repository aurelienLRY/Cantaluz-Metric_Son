#pragma once
/*
 * Modes.h — Sélecteur de comportement LED vs bruit
 *
 * À quoi sert ce fichier ?
 * ------------------------
 * Point d'entrée unique appelé par le .ino :
 *   modesSetup()  →  au démarrage (setup Arduino)
 *   modesLoop()   →  à chaque tour (loop Arduino)
 *
 * Le mode réel est choisi dans Config.h (MODE_ACTIF).
 * Modes : MODE_IMMEDIAT (ModeImmediat.cpp), MODE_LENT (ModeLent.cpp).
 *
 * Ajouter un nouveau mode :
 *   1. BruitLedMode dans Types.h
 *   2. ModeXxx.h / ModeXxx.cpp
 *   3. #elif dans Modes.cpp
 *   4. MODE_ACTIF dans Config.h
 */

#include <Arduino.h>

// Permet de lancer l'initialisation du mode actif (boot, calibration…)
void modesSetup();

// Permet d'exécuter une boucle du mode actif
void modesLoop();

// Permet de changer le mode en cours d'exécution (MODE_IMMEDIAT ou MODE_LENT)
void modesSetActive(uint8_t mode);
