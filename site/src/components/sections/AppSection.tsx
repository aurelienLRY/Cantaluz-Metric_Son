"use client";

import Image from "next/image";
import { Badge } from "@/components/ui/badge";
import { ButtonLink } from "@/components/ui/button-link";
import { Card, CardContent } from "@/components/ui/card";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Smartphone, Sliders, LayoutDashboard } from "lucide-react";

const steps = [
  "Connectez le téléphone au réseau Wi-Fi « Cantaluz » (mot de passe : cantaluz1).",
  "Ouvrez http://cantaluz.local dans le navigateur — aucune app à installer.",
  "Choisissez le mode, ajustez la sensibilité du micro et lancez une méditation.",
];

export function AppSection() {
  const sectionRef = useScrollReveal({ mediaFromX: -80 });

  return (
    <section
      id="application"
      ref={sectionRef}
      className="scroll-mt-24 border-t border-white/5 bg-muted/20 py-24 md:py-32"
    >
      <div className="mx-auto grid max-w-6xl items-center gap-12 px-6 md:grid-cols-2 md:gap-16">
        <div className="reveal-media flex justify-center">
          <div className="relative">
            <div className="absolute -inset-8 rounded-full bg-sky-500/10 blur-3xl" />
            <div className="relative overflow-hidden rounded-[2rem] border border-white/10 bg-card shadow-2xl">
              <Image
                src="/images/app-mobile.svg"
                alt="Application mobile Cantaluz — placeholder"
                width={400}
                height={700}
                className="h-auto w-[min(100%,280px)] object-cover md:w-[320px]"
              />
            </div>
          </div>
        </div>

        <div className="reveal-text space-y-6">
          <Badge variant="outline" className="border-violet-500/40 text-violet-400">
            L&apos;application
          </Badge>
          <h2 className="font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Pilotage sans fil depuis le téléphone
          </h2>
          <p className="text-muted-foreground leading-relaxed">
            L&apos;interface web est servie directement par la carte. Slogan
            affiché : <em>« Outil d&apos;accompagnement au calme. »</em> —
            dashboard avec sélection de mode, curseur de sensibilité (0–100) et
            lancement des séances de méditation guidée.
          </p>

          <ol className="space-y-3 text-sm text-muted-foreground">
            {steps.map((step, i) => (
              <li key={step} className="flex gap-3">
                <span className="flex size-6 shrink-0 items-center justify-center rounded-full bg-primary text-xs font-medium text-primary-foreground">
                  {i + 1}
                </span>
                <span className="pt-0.5 leading-relaxed">{step}</span>
              </li>
            ))}
          </ol>

          <div className="grid gap-3 pt-2 sm:grid-cols-3">
            <Card className="border-white/10 bg-card/50">
              <CardContent className="flex flex-col items-center gap-2 p-4 text-center">
                <LayoutDashboard className="size-5 text-violet-400" />
                <span className="text-xs font-medium">Dashboard</span>
              </CardContent>
            </Card>
            <Card className="border-white/10 bg-card/50">
              <CardContent className="flex flex-col items-center gap-2 p-4 text-center">
                <Sliders className="size-5 text-violet-400" />
                <span className="text-xs font-medium">Sensibilité</span>
              </CardContent>
            </Card>
            <Card className="border-white/10 bg-card/50">
              <CardContent className="flex flex-col items-center gap-2 p-4 text-center">
                <Smartphone className="size-5 text-violet-400" />
                <span className="text-xs font-medium">100 % web</span>
              </CardContent>
            </Card>
          </div>

          <ButtonLink href="#modes" variant="secondary">
            Découvrir les trois modes
          </ButtonLink>
        </div>
      </div>
    </section>
  );
}
