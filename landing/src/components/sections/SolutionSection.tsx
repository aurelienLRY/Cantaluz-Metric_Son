"use client";

import Image from "next/image";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Badge } from "@/components/ui/badge";
import { CheckCircle2 } from "lucide-react";

const points = [
  "Un feedback sensoriel immédiat, accessible à tous les âges",
  "Les enfants lisent le signal et s'ajustent par eux-mêmes",
  "L'adulte accompagne le groupe, sans jouer le gendarme du silence",
  "Une routine collective que la classe peut s'approprier et co-construire",
];

export function SolutionSection() {
  const ref = useScrollReveal();

  return (
    <section
      id="solution"
      ref={ref}
      className="scroll-mt-24 bg-muted/40 py-20 md:py-28"
    >
      <div className="mx-auto grid max-w-6xl items-center gap-12 px-6 lg:grid-cols-2 lg:gap-16">
        <div className="reveal relative order-2 lg:order-1">
          <div className="overflow-hidden rounded-2xl border border-border/60 bg-card shadow-lg">
            <Image
              src="/images/produit.webp"
              alt="Vumètre pédagogique Cantaluz — photo produit à remplacer"
              width={900}
              height={900}
              className="aspect-square object-cover object-center"
            />
          </div>
        </div>

        <div className="order-1 space-y-6 lg:order-2">
          <Badge variant="outline" className="reveal border-emerald-300 text-emerald-800">
            Ce que fait le produit
          </Badge>
          <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Du son à la lumière : un matériel pour agir ensemble
          </h2>
          <p className="reveal text-lg leading-relaxed text-muted-foreground">
            Un micro capte l&apos;ambiance ; un bandeau LED la traduit en
            lumière. Comme un matériel d&apos;exploration sensorielle, le
            dispositif donne aux enfants un repère objectif sur leur
            environnement sonore — ils voient, comprennent et ajustent leur
            comportement en situation réelle.
          </p>
          <p className="reveal leading-relaxed text-muted-foreground">
            L&apos;enjeu n&apos;est pas de faire taire, mais d&apos;aider chaque
            enfant à prendre conscience de son impact sur le collectif — dans
            l&apos;esprit des pédagogies qui placent l&apos;autonomie et la
            coopération au cœur de l&apos;apprentissage.
          </p>
          <p className="reveal rounded-xl border border-emerald-200 bg-emerald-50 px-5 py-4 text-emerald-900">
            <strong>
              Un outil d&apos;accompagnement et d&apos;expérimentation — jamais
              un instrument de sanction.
            </strong>
          </p>
          <ul className="reveal space-y-3 pt-2">
            {points.map((point) => (
              <li key={point} className="flex gap-3 text-muted-foreground">
                <CheckCircle2 className="mt-0.5 size-5 shrink-0 text-emerald-600" />
                <span>{point}</span>
              </li>
            ))}
          </ul>
        </div>
      </div>
    </section>
  );
}
