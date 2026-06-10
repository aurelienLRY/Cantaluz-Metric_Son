"use client";

import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Badge } from "@/components/ui/badge";
import { UtensilsCrossed, GraduationCap, Clock, Users } from "lucide-react";

const usages = [
  { icon: GraduationCap, label: "Classe" },
  { icon: UtensilsCrossed, label: "Restauration scolaire" },
  { icon: Clock, label: "Accueil périscolaire" },
  { icon: Users, label: "Espaces de regroupement" },
];

export function PourQuiSection() {
  const ref = useScrollReveal();

  return (
    <section
      id="pour-qui"
      ref={ref}
      className="scroll-mt-24 py-20 md:py-28"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="grid gap-12 lg:grid-cols-2 lg:gap-16">
          <div>
            <Badge variant="outline" className="reveal mb-4">
              Pour qui
            </Badge>
            <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
              Pensé pour les établissements qui veulent travailler l&apos;ambiance
              sonore autrement
            </h2>
            <p className="reveal mt-6 leading-relaxed text-muted-foreground">
              Ce produit s&apos;adresse en priorité aux établissements du{" "}
              <strong className="font-medium text-foreground">
                réseau Calendretta
              </strong>
              , mais aussi plus largement aux écoles, cantines et espaces
              éducatifs qui souhaitent responsabiliser les enfants, instaurer
              des routines collectives et faire du cadre sonore un sujet
              pédagogique partagé.
            </p>
            <p className="reveal mt-4 leading-relaxed text-muted-foreground">
              L&apos;argument fort pour Calendretta : l&apos;appropriation par
              les élèves — ils peuvent s&apos;auto-corriger dans un cadre
              collectif, sans intervention permanente de l&apos;adulte.
            </p>
          </div>

          <div className="reveal rounded-2xl border border-border/60 bg-muted/30 p-8">
            <h3 className="font-heading text-lg font-semibold">
              Lieux d&apos;usage
            </h3>
            <ul className="mt-6 space-y-4">
              {usages.map((u) => (
                <li
                  key={u.label}
                  className="flex items-center gap-4 rounded-xl border border-border/40 bg-background px-4 py-3"
                >
                  <div className="flex size-10 items-center justify-center rounded-lg bg-emerald-50 text-emerald-700">
                    <u.icon className="size-5" />
                  </div>
                  <span className="font-medium">{u.label}</span>
                </li>
              ))}
            </ul>
          </div>
        </div>
      </div>
    </section>
  );
}
