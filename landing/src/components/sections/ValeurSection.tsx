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
          Apprendre à habiter son espace, ensemble
        </h2>
        <p className="reveal mx-auto mt-6 max-w-2xl text-lg leading-relaxed text-muted-foreground">
          Cantaluz ne remplace pas l&apos;adulte : il lui offre un support
          concret pour accompagner les enfants vers plus d&apos;autonomie, de
          coopération et de respect du collectif — les valeurs au cœur des
          pédagogies Montessori et Freinet.
        </p>
        <blockquote className="reveal mt-8 border-l-4 border-emerald-500 pl-6 text-left italic text-muted-foreground md:mx-auto md:max-w-xl md:border-l-0 md:pl-0 md:text-center md:not-italic">
          « Le bruit devient une expérience visible que le groupe peut observer,
          nommer et réguler. Les enfants ne subissent plus une consigne : ils
          comprennent l&apos;effet de leur voix et choisissent d&apos;ajuster
          leur comportement — pour eux, et pour les autres. »
        </blockquote>
      </div>
    </section>
  );
}
