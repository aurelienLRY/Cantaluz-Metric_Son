"use client";

import Image from "next/image";
import { Badge } from "@/components/ui/badge";
import { Card, CardContent } from "@/components/ui/card";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Mic, Wifi, Lightbulb } from "lucide-react";

const features = [
  {
    icon: Mic,
    title: "Micro MAX4466",
    text: "Mesure l'ambiance sonore de la classe en temps réel.",
  },
  {
    icon: Lightbulb,
    title: "Ruban WS2812B",
    text: "Barre lumineuse du vert à l'orange puis au rouge selon l'intensité.",
  },
  {
    icon: Wifi,
    title: "Wi-Fi embarqué",
    text: "Réseau Cantaluz · pilotage depuis http://cantaluz.local",
  },
];

export function ProjetSection() {
  const sectionRef = useScrollReveal({ mediaFromX: -60 });

  return (
    <section
      id="projet"
      ref={sectionRef}
      className="scroll-mt-24 border-t border-white/5 py-24 md:py-32"
    >
      <div className="mx-auto grid max-w-6xl items-center gap-12 px-6 md:grid-cols-2 md:gap-16">
        <div className="reveal-media relative">
          <div className="absolute -inset-4 rounded-3xl bg-gradient-to-br from-emerald-500/20 via-transparent to-rose-500/20 blur-2xl" />
          <div className="relative overflow-hidden rounded-2xl border border-white/10 shadow-2xl">
            <Image
              src="/images/hero.webp"
              alt="Cantaluz en classe"
              width={800}
              height={500}
              className="h-auto w-full object-cover"
            />
          </div>
        </div>

        <div className="reveal-text space-y-6">
          <Badge variant="outline" className="border-emerald-500/40 text-emerald-400">
            Le projet
          </Badge>
          <h2 className="font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Un outil d&apos;accompagnement au calme
          </h2>
          <p className="text-muted-foreground leading-relaxed">
            Cantaluz est né d&apos;une idée simple : rendre le niveau sonore{" "}
            <em>visible</em> pour aider élèves et enseignants à réguler
            l&apos;ambiance. Le nom mêle <em>canta</em> (chanter) et{" "}
            <em>luz</em> (lumière) — la voix de la classe traduite en lumière.
          </p>
          <p className="text-muted-foreground leading-relaxed">
            Conçu comme projet pédagogique open source — électronique,
            programmation embarquée et interface web — documenté sur GitHub
            et utilisable au quotidien en salle de classe.
          </p>

          <div className="grid gap-4 pt-2 sm:grid-cols-1">
            {features.map((f) => (
              <Card key={f.title} className="border-white/10 bg-card/50">
                <CardContent className="flex gap-4 p-4">
                  <div className="flex size-10 shrink-0 items-center justify-center rounded-lg bg-emerald-500/10 text-emerald-400">
                    <f.icon className="size-5" />
                  </div>
                  <div>
                    <h3 className="font-medium">{f.title}</h3>
                    <p className="text-sm text-muted-foreground">{f.text}</p>
                  </div>
                </CardContent>
              </Card>
            ))}
          </div>
        </div>
      </div>
    </section>
  );
}
