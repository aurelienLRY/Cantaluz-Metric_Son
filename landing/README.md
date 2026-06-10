# Cantaluz — Site marketing

One-page **orientée produit** pour présenter le vumètre pédagogique Cantaluz aux établissements scolaires (réseau Calendretta et au-delà).

> Site technique du projet : voir le dossier `../site/`

## Démarrage

```bash
cd landing
npm install
npm run dev
```

Ouvrir [http://localhost:3000](http://localhost:3000) — si le site technique tourne déjà sur le port 3000, lancer avec `npm run dev -- -p 3001`.

## Personnalisation

- **Email de contact** : modifier `CONTACT_EMAIL` dans `src/components/sections/ContactSection.tsx`
- **Photos** : remplacer les fichiers dans `public/images/` (voir `LISEZMOI.txt`)

## Sections

1. Hero — promesse produit
2. Le constat — problème du bruit scolaire
3. La solution — fonctionnement pédagogique
4. Caractéristiques — app web embarquée, modes, réglages
5. Pourquoi c'est utile — 3 piliers (pédagogique, concret, collectif)
6. Bénéfices — grille de 6 avantages
7. Pour qui — Calendretta + lieux d'usage
8. Proposition de valeur — citation
9. Contact — démo et projet pilote

## Stack

Next.js 16 · Tailwind CSS v4 · shadcn/ui · GSAP ScrollTrigger
