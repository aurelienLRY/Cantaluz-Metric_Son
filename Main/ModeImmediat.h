#pragma once
/*
 * ModeImmediat.h — Mode « immédiat » (comportement actuel du projet)
 *
 * À quoi sert ce mode ?
 * ---------------------
 *   - Réaction directe au micro (VU qui monte vite)
 *   - Couleurs par zone sur le ruban (vert / orange / rouge)
 *   - Flash bleu à chaque montée de palier sonore
 *   - Descente de barre lente après silence (DESCENT_DELAY_SEC)
 *
 * Activé quand : MODE_ACTIF == MODE_IMMEDIAT dans Config.h
 * Ne pas confondre avec Config.h (réglages) ni Types.h (noms des états).
 */

// Permet d'initialiser ruban, boot, calibration et configApply()
void modeImmediatSetup();

// Permet d'exécuter une boucle : micro → barre → flash → affichage LED
void modeImmediatLoop();
