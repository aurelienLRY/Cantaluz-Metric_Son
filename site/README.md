# Site vitrine Cantaluz

One-page de présentation du projet pédagogique **Cantaluz**, avec animations au scroll (GSAP ScrollTrigger) et composants [shadcn/ui](https://ui.shadcn.com).

## Démarrage

```bash
cd site
npm install
npm run dev
```

Ouvrir [http://localhost:3000](http://localhost:3000).

## Build production

```bash
npm run build
npm start
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

1. Hero — accroche animée
2. Projet — présentation générale
3. Objectifs pédagogiques
4. Boîtier — specs + photos
5. Application web embarquée
6. Les trois modes (Flash, Standard, Méditation)
