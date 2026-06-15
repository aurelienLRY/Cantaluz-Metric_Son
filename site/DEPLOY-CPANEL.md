# Déploiement cPanel (O2switch) — site technique

Export statique Next.js : uploadez le contenu du dossier **`out/`** dans `public_html/`.

## Build

```bash
cd site
npm install
npm run build
```

Le dossier **`site/out/`** contient le site prêt pour cPanel.

## Upload cPanel

1. Gestionnaire de fichiers → `public_html/` (ou sous-domaine dédié, ex. `doc.votredomaine.fr`)
2. Uploadez **tout le contenu** de `out/` (pas le dossier `out` lui-même)
3. Vérifiez que `index.html` est à la racine

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

## Mise à jour

```bash
cd site
npm run build
```

Re-uploader le contenu de `out/` (au minimum `index.html`, `_next/` et ce qui a changé).

## Erreurs fréquentes

| Problème | Solution |
|----------|----------|
| Page blanche | Uploader le **contenu** de `out/`, pas le projet source |
| Sans CSS | Vérifier que `_next/` est bien uploadé |
| 404 pages légales | URLs avec slash final : `/mentions-legales/` |

> Site marketing : voir `../landing/DEPLOY-CPANEL.md`
