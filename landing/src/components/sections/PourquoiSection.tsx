"use client";

import Image from "next/image";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { Card, CardContent } from "@/components/ui/card";
import { Ear, HeartHandshake, Users } from "lucide-react";

const pillars = [
  {
    icon: Ear,
    title: "Pédagogique",
    text: "On apprend à écouter et à se réguler — le bruit devient un sujet d'apprentissage concret.",
  },
  {
    icon: Users,
    title: "Concret",
    text: "Le signal LED est immédiat et lisible par tous les âges, sans formation complexe.",
  },
  {
    icon: HeartHandshake,
    title: "Collectif",
    text: "L'outil améliore l'ambiance sans culpabiliser les enfants : un repère partagé par le groupe.",
  },
];

export function PourquoiSection() {
  const ref = useScrollReveal();

  return (
    <section ref={ref} className="py-20 md:py-28">
      <div className="mx-auto max-w-6xl px-6">
        <div className="mx-auto max-w-2xl text-center">
          <h2 className="reveal font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Pourquoi c&apos;est utile
          </h2>
          <p className="reveal mt-5 text-lg leading-relaxed text-muted-foreground">
            Le bruit excessif peut nuire à l&apos;attention, aux apprentissages
            et au confort de tous dans une classe ou une cantine. En rendant ce
            bruit visible, le vumètre aide les élèves à devenir{" "}
            <strong className="font-medium text-foreground">
              acteurs de l&apos;ambiance sonore
            </strong>{" "}
            plutôt que simples exécutants des consignes adultes.
          </p>
          <p className="reveal mt-4 text-muted-foreground leading-relaxed">
            Pour les équipes éducatives, c&apos;est un support simple à mettre en
            place, facile à expliquer et immédiatement utile au quotidien.
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
            src="/images/enfants.svg"
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
