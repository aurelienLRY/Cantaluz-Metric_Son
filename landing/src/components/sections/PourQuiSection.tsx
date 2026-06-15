"use client";

import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Badge } from "@/components/ui/badge";
import { UtensilsCrossed, GraduationCap, Clock, Users } from "lucide-react";

const usages = [
  { icon: GraduationCap, label: "Classes Montessori et Freinet" },
  { icon: UtensilsCrossed, label: "Restaurants scolaires" },
  { icon: Clock, label: "Temps d'atelier et périscolaire" },
  { icon: Users, label: "Conseils de classe et regroupements" },
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
              Pour les équipes qui croient à l&apos;autonomie des enfants
            </h2>
            <p className="reveal mt-6 leading-relaxed text-muted-foreground">
              Cantaluz s&apos;adresse aux établissements du{" "}
              <strong className="font-medium text-foreground">
                réseau Calendretta
              </strong>{" "}
              et, plus largement, à toute école engagée dans une pédagogie
              active : Montessori, Freinet, coopération, éducation inclusive.
            </p>
            <p className="reveal mt-4 leading-relaxed text-muted-foreground">
              C&apos;est un outil pour les enseignants qui veulent travailler
              le cadre sonore comme un{" "}
              <strong className="font-medium text-foreground">
                objet d&apos;apprentissage vivant
              </strong>{" "}
              — instaurer des routines avec les enfants, expérimenter, débriefer
              et faire évoluer les usages au fil de l&apos;année.
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
