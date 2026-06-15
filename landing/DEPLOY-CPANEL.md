# Déploiement sur cPanel (O2switch) — site landing

Ce site Next.js est configuré en **export statique** : vous uploadez le dossier `out/`, pas le code source.

## Prérequis sur votre PC

- Node.js 20+ installé
- Le dossier `landing/` du projet

## Étape 1 — Build en local

```bash
cd landing
npm install
npm run build
```

Si tout va bien, le dossier **`landing/out/`** est créé avec :
- `index.html`
- `mentions-legales/`
- `politique-cookies/`
- `_next/` (CSS, JS)
- `images/` (vos photos)

> **Important** : ne uploadez pas `node_modules`, `.next`, ni le code source sur cPanel pour cette méthode.

## Étape 2 — Préparer l’upload

1. Ouvrez le dossier `landing/out/`
2. **Sélectionnez tout le contenu** à l’intérieur (`index.html`, `_next`, `images`, etc.)
3. Compressez en **ZIP** (optionnel mais pratique)

## Étape 3 — cPanel O2switch

1. Connectez-vous à **cPanel** (O2switch)
2. Ouvrez **Gestionnaire de fichiers**
3. Allez dans le bon répertoire :
   - **Site principal** → `public_html/`
   - **Sous-domaine** → `public_html/sous-domaine/` (ex. `landing.votredomaine.fr`)
4. **Videz** l’ancien contenu si vous refaites un déploiement (sauf ce que vous voulez garder)
5. **Uploadez** le contenu de `out/` (ou décompressez le ZIP ici)
6. Vérifiez que `index.html` est **directement** dans `public_html/` (pas dans un sous-dossier `out/`)

Structure attendue :

```
public_html/
├── index.html
├── 404.html
├── .htaccess
├── _next/
├── images/
├── mentions-legales/
└── politique-cookies/
```

## Étape 4 — Vérifications

- [ ] `https://votredomaine.fr/` affiche la page d’accueil
- [ ] `https://votredomaine.fr/mentions-legales/` fonctionne
- [ ] `https://votredomaine.fr/politique-cookies/` fonctionne
- [ ] La bannière cookies apparaît à la première visite
- [ ] Les images dans `images/` se chargent (F12 → onglet Réseau)

## Erreurs fréquentes

| Symptôme | Cause probable | Solution |
|----------|----------------|----------|
| Page blanche | Mauvais dossier uploadé | Uploader le **contenu** de `out/`, pas le projet entier |
| 403 Forbidden | `index.html` manquant ou mauvais chemin | `index.html` doit être à la racine de `public_html` |
| CSS / JS cassés | Dossier `_next/` absent ou incomplet | Re-uploader tout `_next/` après un nouveau build |
| Images cassées | Dossier `images/` manquant | Vérifier `public/images/` avant build, puis `out/images/` |
| 404 sur les pages légales | Ancien déploiement sans `trailingSlash` | Refaire `npm run build` avec la config actuelle |
| « Cannot find module » | Tentative de lancer Next.js sur le serveur sans Node | Utiliser l’export statique (`out/`), pas `npm start` |

## Mise à jour du site

À chaque modification :

```bash
cd landing
npm run build
```

Puis re-uploader **tout le contenu** de `out/` (ou au minimum `index.html`, `_next/`, pages modifiées et `images/`).

## Méthode alternative — Node.js (cPanel)

Si vous préférez faire tourner Next.js en Node (non nécessaire pour ce site) :

1. cPanel → **Setup Node.js App**
2. Version Node **20** ou **22**
3. Racine application : dossier contenant `package.json`
4. Commande de démarrage : `npm start`
5. Script de build : `npm run build`
6. **Retirer** `output: "export"` de `next.config.ts` pour cette méthode

Pour O2switch + site vitrine statique, l’**export statique** (dossier `out/`) reste la méthode la plus simple et la plus fiable.

## Contact / responsable

- Éditeur : [opteo-web.fr](https://opteo-web.fr)
- Hébergeur : O2switch
