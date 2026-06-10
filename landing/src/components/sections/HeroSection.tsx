"use client";

import Image from "next/image";
import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ButtonLink } from "@/components/ui/button-link";
import { Badge } from "@/components/ui/badge";
import { ArrowRight, Volume2 } from "lucide-react";

export function HeroSection() {
  const ref = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      gsap.from(".hero-content > *", {
        y: 40,
        opacity: 0,
        duration: 0.85,
        stagger: 0.12,
        ease: "power2.out",
      });
      gsap.from(".hero-visual", {
        x: 40,
        opacity: 0,
        duration: 1,
        delay: 0.3,
        ease: "power2.out",
      });
    },
    { scope: ref },
  );

  return (
    <section
      ref={ref}
      className="relative overflow-hidden bg-gradient-to-b from-emerald-50/80 via-background to-background pt-28 pb-16 md:pt-36 md:pb-24"
    >
      <div className="mx-auto grid max-w-6xl items-center gap-12 px-6 lg:grid-cols-2 lg:gap-16">
        <div className="hero-content">
          <Badge
            variant="secondary"
            className="mb-6 border border-emerald-200 bg-emerald-50 text-emerald-800"
          >
            <Volume2 className="mr-1.5 size-3.5" />
            Vumètre pédagogique pour l&apos;école
          </Badge>

          <h1 className="font-heading text-4xl font-bold leading-[1.12] tracking-tight text-foreground sm:text-5xl lg:text-[3.25rem]">
            Rendez le bruit visible.{" "}
            <span className="text-emerald-700">
              Aidez les élèves à s&apos;autoréguler.
            </span>
          </h1>

          <p className="mt-6 max-w-xl text-lg leading-relaxed text-muted-foreground">
            Notre vumètre pédagogique transforme le bruit ambiant en signal
            lumineux simple et lisible. Installé en classe ou en cantine, il
            aide les enfants à ajuster leur volume sonore en temps réel — sans
            conflit et sans répétition permanente des consignes.
          </p>

          <div className="mt-10 flex flex-wrap gap-4">
            <ButtonLink href="#contact" size="lg" className="gap-2">
              Demander une démo
              <ArrowRight className="size-4" />
            </ButtonLink>
            <ButtonLink href="#solution" size="lg" variant="outline">
              Découvrir le dispositif
            </ButtonLink>
          </div>
        </div>

        <div className="hero-visual relative">
          <div className="absolute -inset-4 rounded-3xl bg-emerald-100/60 blur-2xl" />
          <div className="relative overflow-hidden rounded-2xl border border-emerald-100 shadow-xl shadow-emerald-900/5">
            <Image
              src="/images/hero-cantine.svg"
              alt="Cantine ou classe scolaire — photo à remplacer"
              width={1200}
              height={700}
              className="h-auto w-full object-cover"
              priority
            />
          </div>
        </div>
      </div>
    </section>
  );
}
