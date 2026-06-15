export const PROJECT = {
  name: "Cantaluz",
  tagline: "La lumière qui répond au son",
  githubUrl: "https://github.com/aurelienLRY/Cantaluz-Metric_Son",
  githubRepo: "aurelienLRY/Cantaluz-Metric_Son",
  cloneUrl: "https://github.com/aurelienLRY/Cantaluz-Metric_Son.git",
  publisherUrl: "https://opteo-web.fr",
  stack: ["ESP8266", "WS2812B", "MAX4466", "FastLED", "Arduino"],
} as const;

export const DOCS = [
  {
    file: "README.md",
    title: "Installation & démarrage",
    desc: "Matériel, téléversement Arduino, Wi-Fi, dépannage.",
  },
  {
    file: "Main/Config.h",
    title: "Paramètres firmware",
    desc: "LED, micro, modes, méditation, Wi-Fi — fichier principal à modifier.",
  },
  {
    file: "Main/PARAMETRES.md",
    title: "Référence des paramètres",
    desc: "Tableau détaillé des constantes et de leur effet.",
  },
  {
    file: "Main/FICHIERS.md",
    title: "Guide des fichiers",
    desc: "Rôle de chaque module .cpp / .h du dossier Main.",
  },
  {
    file: "FICHE_UTILISATEUR.md",
    title: "Fiche utilisateur",
    desc: "Mode d'emploi imprimable pour la classe.",
  },
] as const;

export const REPO_TREE = [
  "Main/          → firmware Arduino (sketch Main.ino)",
  "Main/Config.h  → réglages utilisateur",
  "site/          → ce site (documentation technique)",
  "landing/       → site marketing",
  "WifiMinimal/   → test Wi-Fi matériel",
] as const;
