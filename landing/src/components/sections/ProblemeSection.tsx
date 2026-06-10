"use client";

import { useScrollReveal } from "@/hooks/useScrollReveal";
import { AlertCircle } from "lucide-react";

export function ProblemeSection() {
  const ref = useScrollReveal();

  return (
    <section
      id="probleme"
      ref={ref}
      className="scroll-mt-24 border-t border-border/50 py-20 md:py-28"
    >
      <div className="mx-auto max-w-3xl px-6 text-center">
        <div className="reveal mx-auto mb-6 flex size-12 items-center justify-center rounded-full bg-amber-50 text-amber-700">
          <AlertCircle className="size-6" />
        </div>
        <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
          Le bruit se ressent partout, mais on ne le voit pas
        </h2>
        <p className="reveal mt-6 text-lg leading-relaxed text-muted-foreground">
          Dans un établissement scolaire, le bruit ne se voit pas, mais il se
          ressent partout : concentration, fatigue, stress, qualité des échanges,
          ambiance collective. Les ressources sur le bruit en milieu scolaire
          rappellent qu&apos;il est essentiel d&apos;agir à la fois sur
          l&apos;environnement sonore et sur les comportements — notamment dans
          les restaurants scolaires et les salles de classe.
        </p>
        <p className="reveal mt-4 text-lg leading-relaxed text-muted-foreground">
          Notre solution a été pensée pour cela : rendre le niveau sonore{" "}
          <strong className="font-medium text-foreground">
            compréhensible immédiatement
          </strong>
          , afin d&apos;encourager une régulation simple, collective et
          progressive.
        </p>
      </div>
    </section>
  );
}
