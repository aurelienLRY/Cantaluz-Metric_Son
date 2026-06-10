"use client";

import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Quote } from "lucide-react";

export function ValeurSection() {
  const ref = useScrollReveal();

  return (
    <section ref={ref} className="border-y border-border/50 bg-muted/30 py-20 md:py-24">
      <div className="mx-auto max-w-4xl px-6 text-center">
        <Quote className="reveal mx-auto size-10 text-emerald-600/60" />
        <h2 className="reveal mt-6 font-heading text-3xl font-bold tracking-tight md:text-4xl">
          Un boîtier simple pour apprendre à mieux vivre ensemble
        </h2>
        <p className="reveal mx-auto mt-6 max-w-2xl text-lg leading-relaxed text-muted-foreground">
          Le vumètre transforme le bruit en signal utile, visible et éducatif. Il
          aide les enfants à s&apos;auto-évaluer, soutient les adultes dans leur
          mission éducative et contribue à un environnement plus serein au
          quotidien.
        </p>
        <blockquote className="reveal mt-8 border-l-4 border-emerald-500 pl-6 text-left italic text-muted-foreground md:mx-auto md:max-w-xl md:border-l-0 md:pl-0 md:text-center md:not-italic">
          « Dans une classe ou une cantine, le bruit est souvent subi plutôt que
          compris. Notre vumètre pédagogique rend ce bruit visible en temps
          réel. Les élèves voient immédiatement quand l&apos;ambiance devient
          trop sonore et peuvent ajuster leur comportement sans attendre
          l&apos;intervention d&apos;un adulte. »
        </blockquote>
      </div>
    </section>
  );
}
