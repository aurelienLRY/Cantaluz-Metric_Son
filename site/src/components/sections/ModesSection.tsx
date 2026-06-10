"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ScrollTrigger } from "gsap/ScrollTrigger";
import { Badge } from "@/components/ui/badge";
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Zap, Waves, Wind } from "lucide-react";

gsap.registerPlugin(ScrollTrigger);

const modes = [
  {
    id: "flash",
    icon: Zap,
    name: "Flash",
    badge: "Par défaut",
    color: "text-sky-400",
    border: "border-sky-500/30",
    bg: "bg-sky-500/10",
    description:
      "Barre réactive au son avec flashs bleus à chaque palier dépassé. Idéal pour signaler visuellement les pics de bruit.",
    usage: "Séances normales, ateliers, temps d'échange.",
  },
  {
    id: "standard",
    icon: Waves,
    name: "Standard",
    badge: "Fluide",
    color: "text-emerald-400",
    border: "border-emerald-500/30",
    bg: "bg-emerald-500/10",
    description:
      "Même barre vert → orange → rouge, mais montée et descente plus douces, sans flash. Ambiance apaisée.",
    usage: "Travail silencieux, lecture, activité calme prolongée.",
  },
  {
    id: "meditation",
    icon: Wind,
    name: "Méditation guidée",
    badge: "2 · 5 · 10 min",
    color: "text-fuchsia-400",
    border: "border-fuchsia-500/30",
    bg: "bg-fuchsia-500/10",
    description:
      "Micro ignoré. Respiration guidée : cyan (inspire), ambre (retiens), magenta (expire), lavande (air bloqué). LED une par une.",
    usage: "Pause après la récréation, retour au calme collectif.",
  },
];

export function ModesSection() {
  const sectionRef = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      const cards = sectionRef.current?.querySelectorAll(".mode-card");
      if (!cards?.length) return;

      gsap.from(cards, {
        scrollTrigger: {
          trigger: sectionRef.current,
          start: "top 70%",
        },
        y: 80,
        opacity: 0,
        duration: 0.8,
        stagger: 0.15,
        ease: "power3.out",
      });
    },
    { scope: sectionRef },
  );

  return (
    <section
      id="modes"
      ref={sectionRef}
      className="scroll-mt-24 py-24 md:py-32"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="mx-auto max-w-2xl text-center">
          <Badge variant="outline" className="border-rose-500/40 text-rose-400">
            Les trois modes
          </Badge>
          <h2 className="font-heading mt-4 text-3xl font-bold tracking-tight md:text-4xl">
            Adapter la lumière au moment de la classe
          </h2>
          <p className="mt-4 text-muted-foreground">
            Le changement de mode est immédiat depuis l&apos;application.
            Au redémarrage, l&apos;appareil repart en mode Flash.
          </p>
        </div>

        <div className="mt-14 grid gap-6 md:grid-cols-3">
          {modes.map((mode) => (
            <Card
              key={mode.id}
              className={`mode-card border-white/10 bg-card/60 ${mode.border}`}
            >
              <CardHeader>
                <div className="flex items-center justify-between">
                  <div
                    className={`flex size-11 items-center justify-center rounded-xl ${mode.bg} ${mode.color}`}
                  >
                    <mode.icon className="size-5" />
                  </div>
                  <Badge variant="secondary" className="text-xs">
                    {mode.badge}
                  </Badge>
                </div>
                <CardTitle className="mt-4">{mode.name}</CardTitle>
                <CardDescription className="leading-relaxed">
                  {mode.description}
                </CardDescription>
              </CardHeader>
              <CardContent>
                <p className="text-xs text-muted-foreground">
                  <span className="font-medium text-foreground">Cas d&apos;usage : </span>
                  {mode.usage}
                </p>
              </CardContent>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
