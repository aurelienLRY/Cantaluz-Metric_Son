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
  Trophy,
  Globe,
  Plug,
  Palette,
  LayoutGrid,
} from "lucide-react";

const caracteristiques = [
  {
    icon: Globe,
    title: "Application web embarquée",
    text: "L'enseignant pilote le dispositif depuis le navigateur — simple, sans installation.",
  },
  {
    icon: Wifi,
    title: "Pilotage sans fil",
    text: "L'adulte choisit le mode et les réglages ; les enfants interagissent avec le signal lumineux.",
  },
  {
    icon: SlidersHorizontal,
    title: "Sensibilité réglable",
    text: "Adapter le dispositif à chaque espace — classe calme, cantine animée ou atelier coopératif.",
  },
  {
    icon: Palette,
    title: "Signal sensoriel",
    text: "Une lecture visuelle immédiate du bruit, comme un matériel concret au service du groupe.",
  },
  {
    icon: Plug,
    title: "Prêt à l'emploi",
    text: "Brancher, allumer : le dispositif est opérationnel en quelques secondes, prêt à être exploré.",
  },
  {
    icon: LayoutGrid,
    title: "Plusieurs modes",
    text: "Vu-mètre, méditation guidée ou jeu coopératif — un mode pour chaque moment de la journée.",
  },
];

const modes = [
  {
    icon: Zap,
    name: "Flash",
    badge: "Mode par défaut",
    accroche: "Observer pour comprendre",
    description:
      "Le bandeau traduit le bruit en lumière en temps réel. Les enfants voient l'effet de leur voix sur le groupe et s'ajustent naturellement — l'adulte n'a plus à répéter, il peut accompagner la prise de conscience.",
    color: "text-sky-700",
    bg: "bg-sky-50",
    border: "border-sky-200",
  },
  {
    icon: Waves,
    name: "Standard",
    badge: "Ambiance douce",
    accroche: "Un compagnon discret",
    description:
      "Même principe sensoriel, en plus progressif. Idéal pour les temps de travail autonome, la lecture silencieuse ou les ateliers où l'enfant a besoin d'un repère visuel sans stimulation excessive.",
    color: "text-emerald-700",
    bg: "bg-emerald-50",
    border: "border-emerald-200",
  },
  {
    icon: Wind,
    name: "Méditation guidée",
    badge: "2 · 5 · 10 min",
    accroche: "Un temps pour souffler ensemble",
    description:
      "La lumière accompagne la respiration du groupe — un rituel collectif pour retrouver le calme. Le micro est mis de côté : c'est un moment de pause partagé, à instaurer avec les enfants comme une routine de vie.",
    color: "text-violet-700",
    bg: "bg-violet-50",
    border: "border-violet-200",
  },
  {
    icon: Trophy,
    name: "Défi Fifou",
    badge: "Jeu coopératif · 2 · 5 · 10 min",
    accroche: "Le silence fait avancer le groupe",
    description:
      "Un jeu collectif où le bandeau ne progresse qu'en l'absence de bruit. Les enfants coopèrent pour remplir le ruban avant la fin du chrono — ils expérimentent, s'auto-évaluent et découvrent que le calme est la clé du succès commun.",
    color: "text-cyan-700",
    bg: "bg-cyan-50",
    border: "border-cyan-200",
    featured: true,
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
            Un dispositif simple, au service de la pédagogie
          </h2>
          <p className="reveal mt-4 text-muted-foreground leading-relaxed">
            Cantaluz se met en place en quelques minutes. L&apos;enseignant
            choisit le mode adapté au moment vécu par le groupe ; les enfants
            interagissent avec un signal concret, lisible et partagé — sans
            formation technique, sans complexité.
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
                src="/images/app.webp"
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
              L&apos;adulte guide, les enfants expérimentent
            </h3>
            <p className="leading-relaxed text-muted-foreground">
              Depuis un simple navigateur, l&apos;enseignant choisit le mode et
              adapte la sensibilité à l&apos;espace. Les enfants, eux,
              interagissent avec le signal lumineux — c&apos;est leur terrain
              d&apos;expérimentation et d&apos;autorégulation.
            </p>
            <ul className="space-y-2 text-sm text-muted-foreground">
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Quatre modes pour accompagner chaque moment de la journée
              </li>
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Sensibilité ajustable selon l&apos;espace et le groupe
              </li>
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Méditation collective ou jeu coopératif (Défi Fifou)
              </li>
              <li className="flex gap-2">
                <span className="text-emerald-600">•</span>
                Interface claire, pensée pour un usage en classe
              </li>
            </ul>
          </div>
        </div>

        <Separator className="reveal my-16" />

        <div className="reveal mx-auto max-w-2xl text-center">
          <h3 className="font-heading text-2xl font-bold tracking-tight md:text-3xl">
            Quatre façons d&apos;accompagner le groupe
          </h3>
          <p className="mt-3 text-muted-foreground leading-relaxed">
            Observer, accompagner, souffler ou jouer ensemble — chaque mode
            répond à un besoin différent de la vie de classe, dans le respect
            de l&apos;autonomie et de la coopération.
          </p>
        </div>

        <div className="mt-10 grid gap-6 md:grid-cols-2 lg:grid-cols-4">
          {modes.map((mode) => (
            <Card
              key={mode.name}
              className={`reveal border ${mode.border} ${mode.bg} shadow-sm ${
                mode.featured ? "ring-2 ring-cyan-300/60" : ""
              }`}
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
                <p className={`text-sm font-medium ${mode.color}`}>
                  {mode.accroche}
                </p>
                <CardDescription className="leading-relaxed text-foreground/70">
                  {mode.description}
                </CardDescription>
              </CardHeader>
            </Card>
          ))}
        </div>

        <div className="reveal mt-10 rounded-2xl border border-cyan-200 bg-gradient-to-br from-cyan-50 to-emerald-50 p-8 md:p-10">
          <div className="mx-auto max-w-3xl text-center">
            <Badge className="mb-4 bg-cyan-700 text-white hover:bg-cyan-700">
              Jeu coopératif · Défi Fifou
            </Badge>
            <h4 className="font-heading text-xl font-bold tracking-tight md:text-2xl">
              Apprendre en jouant, progresser en silence
            </h4>
            <p className="mt-4 leading-relaxed text-muted-foreground">
              Dans l&apos;esprit Freinet du jeu comme levier d&apos;apprentissage,
              le Défi Fifou inverse la logique :{" "}
              <strong className="text-foreground">
                le bandeau n&apos;avance que lorsque le groupe reste calme
              </strong>
              . Les enfants coopèrent, s&apos;auto-évaluent et découvrent par
              l&apos;expérience que leur comportement individuel nourrit la
              réussite collective — sans note, sans sanction, avec la joie
              d&apos;avancer ensemble.
            </p>
          </div>
        </div>
      </div>
    </section>
  );
}
