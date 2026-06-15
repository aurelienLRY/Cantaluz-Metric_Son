"use client";

import Image from "next/image";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Card, CardContent } from "@/components/ui/card";
import { Hand, Layers, Users } from "lucide-react";

const pillars = [
  {
    icon: Hand,
    title: "Autonomie",
    text: "L'enfant observe le signal, évalue la situation et agit par lui-même — l'adulte guide sans imposer.",
  },
  {
    icon: Layers,
    title: "Concret",
    text: "La lumière rend tangible ce qui était invisible : une expérience sensorielle directe, à la manière du matériel Montessori.",
  },
  {
    icon: Users,
    title: "Coopération",
    text: "Le groupe construit ensemble son cadre sonore — dans l'esprit Freinet de la vie communautaire et de la responsabilité partagée.",
  },
];

export function PourquoiSection() {
  const ref = useScrollReveal();

  return (
    <section ref={ref} className="py-20 md:py-28">
      <div className="mx-auto max-w-6xl px-6">
        <div className="mx-auto max-w-2xl text-center">
          <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
            En phase avec les pédagogies actives
          </h2>
          <p className="reveal mt-5 text-lg leading-relaxed text-muted-foreground">
            Cantaluz s&apos;inscrit dans une logique que partagent Montessori et
            Freinet : donner aux enfants les moyens de{" "}
            <strong className="font-medium text-foreground">
              se réguler eux-mêmes
            </strong>
            , par l&apos;expérience et le travail collectif — plutôt que par
            des rappels répétés de l&apos;adulte.
          </p>
          <p className="reveal mt-4 text-muted-foreground leading-relaxed">
            L&apos;enseignant devient accompagnateur du groupe : il installe le
            dispositif, propose des routines et laisse les enfants expérimenter,
            s&apos;auto-évaluer et ajuster leur comportement au fil des séances.
          </p>
        </div>

        <div className="reveal mt-14 grid gap-6 md:grid-cols-3">
          {pillars.map((p) => (
            <Card key={p.title} className="border-border/60 bg-card shadow-sm">
              <CardContent className="p-6">
                <div className="mb-4 flex size-11 items-center justify-center rounded-xl bg-emerald-50 text-emerald-700">
                  <p.icon className="size-5" />
                </div>
                <h3 className="font-heading text-lg font-semibold">{p.title}</h3>
                <p className="mt-2 text-sm leading-relaxed text-muted-foreground">
                  {p.text}
                </p>
              </CardContent>
            </Card>
          ))}
        </div>

        <div className="reveal mt-16 overflow-hidden rounded-2xl border border-border/60 shadow-md">
          <Image
            src="/images/cantine.webp"
            alt="Élèves en autonomie — photo à remplacer"
            width={800}
            height={500}
            className="h-auto w-full object-cover"
          />
        </div>
      </div>
    </section>
  );
}
