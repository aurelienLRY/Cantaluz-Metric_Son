"use client";

import { Badge } from "@/components/ui/badge";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { useScrollReveal } from "@/hooks/useScrollReveal";
import { BookOpen, Heart, Users, GraduationCap } from "lucide-react";

const objectifs = [
  {
    icon: Users,
    title: "Régulation collective",
    text: "Visualiser le bruit aide la classe à s'auto-réguler sans réprimande constante.",
  },
  {
    icon: Heart,
    title: "Retour au calme",
    text: "Le mode méditation guide une respiration collective par la lumière.",
  },
  {
    icon: GraduationCap,
    title: "Apprentissage STEAM",
    text: "Capteurs, microcontrôleur, LEDs adressables et interface web embarquée.",
  },
  {
    icon: BookOpen,
    title: "Usage enseignant",
    text: "Réglages immédiats depuis le téléphone : mode, sensibilité, séances.",
  },
];

export function ObjectifSection() {
  const sectionRef = useScrollReveal();

  return (
    <section
      id="objectif"
      ref={sectionRef}
      className="scroll-mt-24 bg-muted/30 py-24 md:py-32"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="reveal-text mx-auto max-w-2xl text-center">
          <Badge variant="outline" className="border-amber-500/40 text-amber-400">
            Objectifs pédagogiques
          </Badge>
          <h2 className="font-heading mt-4 text-3xl font-bold tracking-tight md:text-4xl">
            Pourquoi Cantaluz en classe ?
          </h2>
          <p className="mt-4 text-muted-foreground">
            Allier technologie accessible et bien-être en milieu scolaire —
            un dispositif concret que les élèves peuvent comprendre et dont
            l&apos;enseignant garde la main.
          </p>
        </div>

        <div className="reveal-text mt-14 grid gap-6 sm:grid-cols-2">
          {objectifs.map((obj) => (
            <Card
              key={obj.title}
              className="reveal-text border-white/10 bg-card/60 transition-colors hover:border-emerald-500/30"
            >
              <CardHeader className="flex flex-row items-center gap-4 space-y-0">
                <div className="flex size-11 items-center justify-center rounded-xl bg-amber-500/10 text-amber-400">
                  <obj.icon className="size-5" />
                </div>
                <CardTitle className="text-lg">{obj.title}</CardTitle>
              </CardHeader>
              <CardContent>
                <p className="text-sm text-muted-foreground leading-relaxed">
                  {obj.text}
                </p>
              </CardContent>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
