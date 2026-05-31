#pragma once
/*
 * WifiPortal.h — Point d'accès Wi-Fi + page web (téléphone)
 *
 * La carte crée le réseau WIFI_AP_SSID (Config.h).
 * App web directe : http://cantaluz.local (modes, réglages, bulles d'aide).
 */

// Démarre le radio SoftAP le plus tôt possible (avant FastLED / ruban)
bool wifiPortalStartRadio();

// Démarre le serveur HTTP (après init LED, quand la RAM est stabilisée)
void wifiPortalStartWeb();

// Radio + web (un seul appel si besoin)
void wifiPortalSetup();

// Traiter les requêtes web (chaque loop)
void wifiPortalLoop();
