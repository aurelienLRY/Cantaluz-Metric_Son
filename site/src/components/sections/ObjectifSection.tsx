"use client";

import { Badge } from "@/components/ui/badge";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Cpu, Layers, Radio, Smartphone } from "lucide-react";

const modules = [
  {
    icon: Cpu,
    title: "MicSensor + Modes",
    text: "Lecture ADC, barre VU, dispatch Flash / Standard / Méditation / Défi Fifou.",
  },
  {
    icon: Layers,
    title: "LedStrip + FlashEtat",
    text: "WS2812B, couleurs par zone, séquence de boot, flashs bleus.",
  },
  {
    icon: Radio,
    title: "WifiPortal",
    text: "SoftAP Cantaluz, mDNS, API REST /api/*, portail captif.",
  },
  {
    icon: Smartphone,
    title: "WebAppHtml.h",
    text: "Interface mobile servie en PROGMEM — dashboard, réglages, séances.",
  },
];

export function ObjectifSection() {
  const sectionRef = useScrollReveal();

  return (
    <section
      id="architecture"
      ref={sectionRef}
      className="scroll-mt-24 bg-muted/30 py-24 md:py-32"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="reveal-text mx-auto max-w-2xl text-center">
          <Badge variant="outline" className="border-amber-500/40 text-amber-400">
            Architecture
          </Badge>
          <h2 className="font-heading mt-4 text-3xl font-bold tracking-tight md:text-4xl">
            Firmware modulaire, config centralisée
          </h2>
          <p className="mt-4 text-muted-foreground leading-relaxed">
            Le dossier <code className="text-foreground">Main/</code> sépare
            capteur, LEDs, Wi-Fi et modes. Les réglages par défaut vivent dans{" "}
            <code className="text-foreground">Config.h</code> ; l&apos;app web
            surcharge temporairement via <code className="text-foreground">LiveConfig</code>.
          </p>
        </div>

        <div className="reveal-text mt-14 grid gap-5 sm:grid-cols-2">
          {modules.map((m) => (
            <Card
              key={m.title}
              className="border-white/10 bg-card/60 transition-colors hover:border-emerald-500/25"
            >
              <CardHeader className="flex flex-row items-center gap-4 space-y-0">
                <div className="flex size-11 items-center justify-center rounded-xl bg-amber-500/10 text-amber-400">
                  <m.icon className="size-5" />
                </div>
                <CardTitle className="text-lg">{m.title}</CardTitle>
              </CardHeader>
              <CardContent>
                <p className="text-sm text-muted-foreground leading-relaxed">
                  {m.text}
                </p>
              </CardContent>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
