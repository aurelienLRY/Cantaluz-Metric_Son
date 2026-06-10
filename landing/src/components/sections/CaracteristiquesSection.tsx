"use client";

import Image from "next/image";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Badge } from "@/components/ui/badge";
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Separator } from "@/components/ui/separator";
import {
  Smartphone,
  Wifi,
  SlidersHorizontal,
  Zap,
  Waves,
  Wind,
  Globe,
  Plug,
  Palette,
  Timer,
} from "lucide-react";

const caracteristiques = [
  {
    icon: Globe,
    title: "Application web embarquée",
    text: "Interface servie directement par le boîtier — aucune application à télécharger.",
  },
  {
    icon: Wifi,
    title: "Pilotage sans fil",
    text: "Connexion Wi-Fi dédiée depuis un smartphone ou une tablette, sans câble.",
  },
  {
    icon: SlidersHorizontal,
    title: "Sensibilité réglable",
    text: "Curseur dans l'app pour adapter la réactivité du micro à chaque espace.",
  },
  {
    icon: Palette,
    title: "Signal couleur progressif",
    text: "Bandeau vert → orange → rouge : la hauteur de la barre reflète le niveau sonore.",
  },
  {
    icon: Plug,
    title: "Prêt à l'emploi",
    text: "Séquence de démarrage automatique : l'appareil est opérationnel en quelques secondes.",
  },
  {
    icon: Timer,
    title: "Méditation guidée",
    text: "Séances de 2, 5 ou 10 minutes avec respiration guidée par la lumière.",
  },
];

const modes = [
  {
    icon: Zap,
    name: "Flash",
    badge: "Mode par défaut",
    description:
      "Barre réactive au son avec flashs bleus aux paliers dépassés. Idéal pour signaler les pics de bruit en cantine ou en classe.",
    color: "text-sky-700",
    bg: "bg-sky-50",
    border: "border-sky-200",
  },
  {
    icon: Waves,
    name: "Standard",
    badge: "Ambiance fluide",
    description:
      "Même barre lumineuse, montée et descente plus douces, sans flash. Parfait pour le travail silencieux ou la lecture.",
    color: "text-emerald-700",
    bg: "bg-emerald-50",
    border: "border-emerald-200",
  },
  {
    icon: Wind,
    name: "Méditation guidée",
    badge: "2 · 5 · 10 min",
    description:
      "Le micro est ignoré. Respiration collective guidée par la lumière — retour au calme après la récréation ou avant une évaluation.",
    color: "text-violet-700",
    bg: "bg-violet-50",
    border: "border-violet-200",
  },
];

export function CaracteristiquesSection() {
  const ref = useScrollReveal();

  return (
    <section
      id="caracteristiques"
      ref={ref}
      className="scroll-mt-24 border-t border-border/50 py-20 md:py-28"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="mx-auto max-w-2xl text-center">
          <Badge variant="outline" className="reveal mb-4 border-emerald-300 text-emerald-800">
            Caractéristiques
          </Badge>
          <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Simple à installer, simple à piloter
          </h2>
          <p className="reveal mt-4 text-muted-foreground leading-relaxed">
            Cantaluz combine un boîtier autonome et une application web intégrée.
            L&apos;équipe éducative garde la main sur le mode et les réglages,
            depuis le téléphone de l&apos;enseignant — sans formation technique.
          </p>
        </div>

        <div className="mt-14 grid gap-5 sm:grid-cols-2 lg:grid-cols-3">
          {caracteristiques.map((c) => (
            <Card
              key={c.title}
              className="reveal border-border/50 bg-background shadow-sm"
            >
              <CardContent className="flex gap-4 p-5">
                <div className="flex size-10 shrink-0 items-center justify-center rounded-lg bg-emerald-50 text-emerald-700">
                  <c.icon className="size-5" />
                </div>
                <div>
                  <h3 className="font-medium">{c.title}</h3>
                  <p className="mt-1 text-sm leading-relaxed text-muted-foreground">
                    {c.text}
                  </p>
                </div>
              </CardContent>
            </Card>
          ))}
        </div>

        <div className="reveal mt-20 grid items-center gap-12 lg:grid-cols-2 lg:gap-16">
          <div className="flex justify-center">
            <div className="overflow-hidden rounded-2xl border border-emerald-100 bg-emerald-50/50 shadow-lg">
              <Image
                src="/images/app-mobile.svg"
                alt="Application web Cantaluz sur smartphone — photo à remplacer"
                width={400}
                height={700}
                className="h-auto w-[min(100%,260px)] object-cover md:w-[280px]"
              />
            </div>
          </div>

          <div className="space-y-5">
            <div className="flex size-11 items-center justify-center rounded-xl bg-emerald-100 text-emerald-700">
              <Smartphone className="size-5" />
            </div>
            <h3 className="font-heading text-2xl font-bold tracking-tight">
              Pilotable depuis une application web embarquée
            </h3>
            <p className="leading-relaxed text-muted-foreground">
              Connectez un smartphone au réseau Wi-Fi du boîtier, ouvrez la page
              dans le navigateur : c&apos;est tout. Pas de store, pas de mise à
              jour à gérer côté établissement.
            </p>
            <ul className="space-y-2 text-sm text-muted-foreground">
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Choix du mode en un clic — effet immédiat sur le ruban
              </li>
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Réglage de la sensibilité du micro selon la salle ou la cantine
              </li>
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Lancement des séances de méditation guidée (2, 5 ou 10 min)
              </li>
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Tableau de bord clair, pensé pour un usage en classe
              </li>
            </ul>
          </div>
        </div>

        <Separator className="reveal my-16" />

        <div className="reveal mx-auto max-w-2xl text-center">
          <h3 className="font-heading text-2xl font-bold tracking-tight md:text-3xl">
            Trois modes pour s&apos;adapter à chaque moment
          </h3>
          <p className="mt-3 text-muted-foreground">
            Flash pour la signalisation nette, Standard pour l&apos;accompagnement
            discret, Méditation pour le retour au calme collectif.
          </p>
        </div>

        <div className="mt-10 grid gap-6 md:grid-cols-3">
          {modes.map((mode) => (
            <Card
              key={mode.name}
              className={`reveal border ${mode.border} ${mode.bg} shadow-sm`}
            >
              <CardHeader>
                <div className="flex items-center justify-between">
                  <div
                    className={`flex size-10 items-center justify-center rounded-lg bg-white/80 ${mode.color}`}
                  >
                    <mode.icon className="size-5" />
                  </div>
                  <Badge variant="secondary" className="text-xs">
                    {mode.badge}
                  </Badge>
                </div>
                <CardTitle className="mt-3">{mode.name}</CardTitle>
                <CardDescription className="leading-relaxed text-foreground/70">
                  {mode.description}
                </CardDescription>
              </CardHeader>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
