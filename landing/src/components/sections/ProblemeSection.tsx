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
          Le bruit est un phénomène invisible — difficile à nommer pour un enfant
        </h2>
        <p className="reveal mt-6 text-lg leading-relaxed text-muted-foreground">
          Dans une classe ou une cantine, l&apos;ambiance sonore influence la
          concentration, les échanges et le bien-être du groupe. Pourtant, le
          bruit reste abstrait : on le subit plus qu&apos;on le comprend.
          Les pédagogies Montessori et Freinet invitent à rendre l&apos;expérience{" "}
          <em>concrète</em> pour que l&apos;enfant puisse agir dessus — pas
          seulement obéir à une consigne.
        </p>
        <p className="reveal mt-4 text-lg leading-relaxed text-muted-foreground">
          Cantaluz répond à ce besoin : transformer le niveau sonore en signal
          lumineux{" "}
          <strong className="font-medium text-foreground">
            immédiatement lisible
          </strong>
          , pour favoriser l&apos;autorégulation, la coopération et la prise de
          conscience collective — au rythme du groupe, pas par la contrainte.
        </p>
      </div>
    </section>
  );
}
