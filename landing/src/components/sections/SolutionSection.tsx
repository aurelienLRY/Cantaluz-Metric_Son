"use client";

import Image from "next/image";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Badge } from "@/components/ui/badge";
import { CheckCircle2 } from "lucide-react";

const points = [
  "Signal rassurant quand l'ambiance reste calme",
  "Lumière plus visible quand le niveau sonore monte",
  "Alerte douce pour le groupe, sans sanction",
  "Repère concret pour doser la voix selon le moment",
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
              src="/images/produit.svg"
              alt="Vumètre pédagogique Cantaluz — photo produit à remplacer"
              width={900}
              height={600}
              className="h-auto w-full object-cover"
            />
          </div>
        </div>

        <div className="order-1 space-y-6 lg:order-2">
          <Badge variant="outline" className="reveal border-emerald-300 text-emerald-800">
            Ce que fait le produit
          </Badge>
          <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Un boîtier qui traduit le bruit en lumière
          </h2>
          <p className="reveal text-lg leading-relaxed text-muted-foreground">
            Le boîtier capte le bruit ambiant grâce à un micro intégré, puis le
            traduit sur un bandeau LED. Quand l&apos;ambiance reste calme, le
            signal est rassurant ; quand le niveau sonore monte, la lumière
            devient plus visible pour alerter le groupe en douceur.
          </p>
          <p className="reveal leading-relaxed text-muted-foreground">
            L&apos;objectif n&apos;est pas de « faire taire » les enfants, mais
            de leur donner un repère concret pour apprendre à mieux doser leur
            voix selon le moment et l&apos;espace.
          </p>
          <p className="reveal rounded-xl border border-emerald-200 bg-emerald-50 px-5 py-4 text-emerald-900">
            <strong>C&apos;est un outil pédagogique, pas un outil de sanction.</strong>
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
