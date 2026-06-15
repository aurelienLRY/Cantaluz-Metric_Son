"use client";

import Image from "next/image";
import { Badge } from "@/components/ui/badge";
import { Card, CardContent } from "@/components/ui/card";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { AlertTriangle, Cable } from "lucide-react";

const connections = [
  { from: "MAX4466", to: "WeMos A0", note: "Sortie analogique du micro" },
  { from: "MAX4466 VCC", to: "3,3 V", note: "Ne pas alimenter en 5 V" },
  { from: "Ruban DIN", to: "D2 (GPIO4)", note: "Résistance 470 Ω en série recommandée" },
  { from: "Ruban 5V", to: "Alimentation 5 V", note: "Externe — pas via USB de la carte" },
  { from: "Ruban GND", to: "GND carte + GND alim", note: "Masse commune obligatoire" },
  { from: "WeMos", to: "USB 5 V", note: "Alimentation carte uniquement" },
];

const warnings = [
  "Ne jamais alimenter le ruban WS2812B depuis la carte — courant trop élevé.",
  "Toujours relier les GND (carte, micro, alimentation ruban).",
  "Ruban de test : LED_COUNT = 17 dans Config.h (économie RAM ESP8266).",
];

export function CablageSection() {
  const sectionRef = useScrollReveal({ mediaFromX: -70, scrub: 1 });

  return (
    <section
      id="cablage"
      ref={sectionRef}
      className="scroll-mt-24 border-t border-white/5 bg-muted/20 py-24 md:py-32"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="reveal-text mx-auto max-w-2xl text-center">
          <Badge variant="outline" className="border-amber-500/40 text-amber-400">
            Câblage
          </Badge>
          <h2 className="font-heading mt-4 text-3xl font-bold tracking-tight md:text-4xl">
            Schéma et connexions
          </h2>
          <p className="mt-4 text-muted-foreground leading-relaxed">
            Architecture simple : une carte ESP8266, un micro analogique et un
            ruban adressable. Le point critique est la{" "}
            <strong className="text-foreground">masse commune</strong> et
            l&apos;alimentation 5 V dédiée au ruban.
          </p>
        </div>

        <div className="reveal-media mt-14 overflow-hidden rounded-2xl border border-white/10 bg-card/40 shadow-xl">
          <Image
            src="/images/schéma.webp"
            alt="Schéma de câblage Cantaluz — remplacer par votre photo"
            width={1000}
            height={620}
            className="h-auto w-full object-contain"
          />
        </div>

        <div className="reveal-text mt-12 grid gap-6 lg:grid-cols-2">
          <Card className="border-white/10 bg-card/50">
            <CardContent className="p-6">
              <div className="mb-4 flex items-center gap-2 text-sky-400">
                <Cable className="size-5" />
                <h3 className="font-medium text-foreground">Tableau de connexion</h3>
              </div>
              <div className="space-y-3 text-sm">
                {connections.map((c) => (
                  <div
                    key={c.from + c.to}
                    className="grid gap-1 border-b border-white/5 pb-3 last:border-0 last:pb-0"
                  >
                    <div className="font-mono text-xs text-emerald-400/90">
                      {c.from} → {c.to}
                    </div>
                    <div className="text-muted-foreground">{c.note}</div>
                  </div>
                ))}
              </div>
            </CardContent>
          </Card>

          <Card className="border-amber-500/20 bg-amber-500/5">
            <CardContent className="p-6">
              <div className="mb-4 flex items-center gap-2 text-amber-400">
                <AlertTriangle className="size-5" />
                <h3 className="font-medium text-foreground">À ne pas oublier</h3>
              </div>
              <ul className="space-y-3 text-sm text-muted-foreground">
                {warnings.map((w) => (
                  <li key={w} className="flex gap-2">
                    <span className="text-amber-500">▸</span>
                    <span>{w}</span>
                  </li>
                ))}
              </ul>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
}
