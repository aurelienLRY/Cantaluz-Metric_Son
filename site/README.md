# Site vitrine Cantaluz

One-page de présentation du projet pédagogique **Cantaluz**, avec animations au scroll (GSAP ScrollTrigger) et composants [shadcn/ui](https://ui.shadcn.com).

## Démarrage

```bash
cd site
npm install
npm run dev
```

Ouvrir [http://localhost:3000](http://localhost:3000).

## Build production (cPanel / O2switch)

```bash
npm run build
```

Le site statique est généré dans **`out/`**. Uploadez son contenu dans `public_html/` sur cPanel.

Guide détaillé : **[DEPLOY-CPANEL.md](./DEPLOY-CPANEL.md)**

## Preview locale après build

```bash
npx serve out
```

## Images

Remplacez les placeholders dans `public/images/` par vos photos (voir `public/images/LISEZMOI.txt`).

Fichiers concernés :
- `boitier.svg` — photo du boîtier
- `ruban.svg` — ruban LED
- `app-mobile.svg` — capture de l'app sur téléphone
- `classe.svg` — utilisation en classe

Si vous utilisez `.jpg` ou `.png`, mettez à jour les chemins dans `src/components/sections/`.

## Stack

- Next.js 16 (App Router)
- Tailwind CSS v4 + shadcn/ui
- GSAP + ScrollTrigger (`@gsap/react`)

## Sections

1. Hero — wiki open source
2. Projet — présentation
3. Architecture — modules firmware
4. Câblage — schéma et connexions
5. Boîtier — specs
6. Application web embarquée
7. Les quatre modes (Flash, Standard, Méditation, Défi Fifou)
8. Wiki — GitHub, quick start, fichiers de doc

## Images

- `schema.svg` → votre photo de schéma de câblage (`schema.jpg` recommandé)
