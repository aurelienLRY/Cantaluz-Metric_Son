"use client";

import Image from "next/image";
import { Badge } from "@/components/ui/badge";
import { Separator } from "@/components/ui/separator";
import { useScrollReveal } from "@/hooks/useScrollReveal";

const specs = [
  { label: "Carte", value: "WeMos D1 mini (ESP8266)" },
  { label: "Capteur son", value: "Micro MAX4466 (analogique)" },
  { label: "Éclairage", value: "Ruban LED WS2812B · 5 V" },
  { label: "Connexion", value: "SoftAP « Cantaluz » · mDNS cantaluz.local" },
  { label: "Interface", value: "Application web embarquée (PROGMEM)" },
  { label: "Démarrage", value: "Séquence bleue → animation verte → écoute" },
];

export function BoitierSection() {
  const sectionRef = useScrollReveal({ mediaFromX: 80, scrub: 1 });

  return (
    <section
      id="boitier"
      ref={sectionRef}
      className="scroll-mt-24 py-24 md:py-32"
    >
      <div className="mx-auto grid max-w-6xl items-center gap-12 px-6 md:grid-cols-2 md:gap-16">
        <div className="reveal-text order-2 space-y-6 md:order-1">
          <Badge variant="outline" className="border-sky-500/40 text-sky-400">
            Le boîtier
          </Badge>
          <h2 className="font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Électronique compacte, prête pour la classe
          </h2>
          <p className="text-muted-foreground leading-relaxed">
            Le cœur du système tient sur une petite carte ESP8266. Le micro
            capte l&apos;ambiance ; le firmware calcule une barre lumineuse et
            pilote chaque LED du ruban. Un bouton marche/arrêt et une LED bleue
            indiquent l&apos;état du Wi-Fi.
          </p>
          <p className="text-sm text-muted-foreground">
            Branchez l&apos;alimentation 5 V, appuyez sur le bouton : la séquence
            de démarrage se lance automatiquement. Voir la section{" "}
            <a href="#cablage" className="text-sky-400 underline underline-offset-2 hover:text-sky-300">
              Câblage
            </a>{" "}
            pour le schéma complet.
          </p>

          <Separator className="bg-white/10" />

          <dl className="grid gap-3 text-sm">
            {specs.map((s) => (
              <div
                key={s.label}
                className="grid grid-cols-[7rem_1fr] gap-2 sm:grid-cols-[8rem_1fr]"
              >
                <dt className="font-medium text-muted-foreground">{s.label}</dt>
                <dd>{s.value}</dd>
              </div>
            ))}
          </dl>
        </div>

            <div className="overflow-hidden rounded-2xl border border-white/10 shadow-xl">
              <Image
                src="/images/produit.webp"
                alt="Boîtier Cantaluz"
                width={800}
                height={800}
                className="h-auto w-full aspect-square object-cover object-center"
                priority
              />
            </div>
   
      </div>
    </section>
  );
}
