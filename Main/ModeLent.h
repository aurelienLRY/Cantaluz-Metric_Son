#pragma once
/*
 * ModeLent.h — Mode « lent » (*dòç*) — ambiance calme
 *
 * Même ruban par zones (vert / orange / rouge), mais :
 *   - montée et descente très adoucies,
 *   - pas de flash bleu,
 *   - boot discret (sans bleu par défaut), luminosité plus douce.
 *
 * Activé : MODE_ACTIF == MODE_LENT dans Config.h
 * Réglages : section MODE LENT dans Config.h
 */

void modeLentSetup();
void modeLentLoop();
