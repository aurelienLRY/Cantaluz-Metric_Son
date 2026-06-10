"use client";

import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Card, CardContent } from "@/components/ui/card";
import {
  Brain,
  Eye,
  MessageCircleOff,
  School,
  Sparkles,
  UsersRound,
} from "lucide-react";

const benefices = [
  {
    icon: Sparkles,
    title: "Autonomie",
    text: "Favoriser l'autonomie des élèves dans la gestion du bruit.",
  },
  {
    icon: School,
    title: "Climat sonore",
    text: "Améliorer le climat sonore dans les classes, couloirs et cantines.",
  },
  {
    icon: MessageCircleOff,
    title: "Moins de rappels",
    text: "Réduire les rappels à l'ordre répétitifs et recentrer l'adulte sur l'accompagnement.",
  },
  {
    icon: Eye,
    title: "Repère visuel",
    text: "Installer un repère visuel commun, compris par tous les âges.",
  },
  {
    icon: UsersRound,
    title: "École inclusive",
    text: "Soutenir une démarche d'école inclusive et d'autorégulation.",
  },
  {
    icon: Brain,
    title: "Attention",
    text: "Contribuer à un environnement propice à la concentration et au calme.",
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
            Bénéfices concrets au quotidien
          </h2>
          <p className="reveal mt-4 text-muted-foreground">
            Le vumètre ne sanctionne pas : il accompagne l&apos;apprentissage du
            calme, de l&apos;attention et du respect du groupe.
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
