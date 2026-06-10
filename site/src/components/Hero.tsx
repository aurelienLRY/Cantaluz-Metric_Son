"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { Badge } from "@/components/ui/badge";
import { ButtonLink } from "@/components/ui/button-link";
import { ArrowDown, Sparkles } from "lucide-react";

export function Hero() {
  const containerRef = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      const tl = gsap.timeline({ defaults: { ease: "power3.out" } });
      tl.from(".hero-badge", { y: 20, opacity: 0, duration: 0.6 })
        .from(".hero-title", { y: 60, opacity: 0, duration: 1 }, "-=0.2")
        .from(".hero-sub", { y: 40, opacity: 0, duration: 0.8 }, "-=0.5")
        .from(".hero-cta", { y: 30, opacity: 0, duration: 0.6, stagger: 0.1 }, "-=0.4")
        .from(".hero-glow", { scale: 0.8, opacity: 0, duration: 1.2 }, "-=0.8");

      gsap.to(".hero-scroll", {
        y: 8,
        repeat: -1,
        yoyo: true,
        duration: 1.4,
        ease: "sine.inOut",
      });
    },
    { scope: containerRef },
  );

  return (
    <section
      ref={containerRef}
      className="relative flex min-h-screen flex-col items-center justify-center overflow-hidden px-6 pt-24 pb-16"
    >
      <div className="hero-glow pointer-events-none absolute inset-0">
        <div className="absolute left-1/2 top-1/3 h-[480px] w-[480px] -translate-x-1/2 -translate-y-1/2 rounded-full bg-emerald-500/20 blur-[120px]" />
        <div className="absolute right-1/4 top-1/2 h-[320px] w-[320px] -translate-y-1/2 rounded-full bg-amber-500/15 blur-[100px]" />
        <div className="absolute bottom-1/4 left-1/4 h-[280px] w-[280px] rounded-full bg-rose-500/10 blur-[90px]" />
      </div>

      <div className="relative z-10 mx-auto max-w-4xl text-center">
        <Badge variant="secondary" className="hero-badge mb-6 gap-1.5 px-3 py-1">
          <Sparkles className="size-3.5 text-amber-400" />
          Projet pédagogique · ESP8266 · ruban WS2812B
        </Badge>

        <h1 className="hero-title font-heading text-5xl font-bold leading-[1.05] tracking-tight sm:text-6xl md:text-7xl">
          La lumière qui{" "}
          <span className="bg-gradient-to-r from-emerald-400 via-amber-400 to-rose-400 bg-clip-text text-transparent">
            répond au son
          </span>
        </h1>

        <p className="hero-sub mx-auto mt-6 max-w-2xl text-lg text-muted-foreground md:text-xl">
          <strong className="text-foreground">Cantaluz</strong> accompagne les
          classes vers le calme : un ruban LED réactif au micro, piloté depuis
          un téléphone via Wi-Fi — sans câble, sans application à installer.
        </p>

        <div className="hero-cta mt-10 flex flex-wrap items-center justify-center gap-4">
          <ButtonLink href="#projet" size="lg">
            Découvrir le projet
          </ButtonLink>
          <ButtonLink href="#boitier" size="lg" variant="outline">
            Voir le boîtier
          </ButtonLink>
        </div>
      </div>

      <a
        href="#projet"
        className="hero-scroll absolute bottom-8 flex flex-col items-center gap-2 text-sm text-muted-foreground transition-colors hover:text-foreground"
        aria-label="Faire défiler"
      >
        <span>Défiler</span>
        <ArrowDown className="size-4" />
      </a>
    </section>
  );
}
