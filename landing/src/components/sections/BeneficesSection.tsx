"use client";

import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Card, CardContent } from "@/components/ui/card";
import {
  Compass,
  Eye,
  Heart,
  Leaf,
  Sparkles,
  UsersRound,
} from "lucide-react";

const benefices = [
  {
    icon: Sparkles,
    title: "Autorégulation",
    text: "Chaque enfant apprend à moduler sa voix en fonction d'un repère objectif — pas d'une menace extérieure.",
  },
  {
    icon: Leaf,
    title: "Climat apaisé",
    text: "Un environnement sonore plus serein, propice à la concentration, à l'écoute et aux temps calmes.",
  },
  {
    icon: Heart,
    title: "Relation bienveillante",
    text: "L'adulte se libère des rappels à l'ordre pour se consacrer à l'accompagnement et à la médiation.",
  },
  {
    icon: Eye,
    title: "Prise de conscience",
    text: "Le signal lumineux aide à nommer l'ambiance, à en parler et à co-construire des règles de vie.",
  },
  {
    icon: UsersRound,
    title: "Vie collective",
    text: "Le groupe apprend à prendre soin de son espace commun — cantine, classe ou atelier.",
  },
  {
    icon: Compass,
    title: "Expérimentation",
    text: "Les enfants testent, observent les effets de leurs actions et progressent à leur rythme.",
  },
];

export function BeneficesSection() {
  const ref = useScrollReveal();

  return (
    <section
      id="benefices"
      ref={ref}
      className="scroll-mt-24 border-t border-border/50 bg-emerald-50/50 py-20 md:py-28"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="mx-auto max-w-2xl text-center">
          <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Ce que cela change au quotidien
          </h2>
          <p className="reveal mt-4 text-muted-foreground leading-relaxed">
            Un dispositif qui respecte l&apos;enfant comme acteur de son
            apprentissage : il voit, comprend, ajuste — et le groupe grandit
            ensemble dans la responsabilité partagée.
          </p>
        </div>

        <div className="mt-14 grid gap-5 sm:grid-cols-2 lg:grid-cols-3">
          {benefices.map((b) => (
            <Card
              key={b.title}
              className="reveal border-border/50 bg-background/80 shadow-sm transition-shadow hover:shadow-md"
            >
              <CardContent className="flex gap-4 p-5">
                <div className="flex size-10 shrink-0 items-center justify-center rounded-lg bg-emerald-100 text-emerald-700">
                  <b.icon className="size-5" />
                </div>
                <div>
                  <h3 className="font-medium">{b.title}</h3>
                  <p className="mt-1 text-sm leading-relaxed text-muted-foreground">
                    {b.text}
                  </p>
                </div>
              </CardContent>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
