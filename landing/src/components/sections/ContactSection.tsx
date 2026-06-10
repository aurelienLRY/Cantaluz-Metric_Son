"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ScrollTrigger } from "gsap/ScrollTrigger";
import { ButtonLink } from "@/components/ui/button-link";
import { Mail, MapPin, ArrowRight } from "lucide-react";

gsap.registerPlugin(ScrollTrigger);

const CONTACT_EMAIL = "contact@cantaluz.fr";

export function ContactSection() {
  const ref = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      gsap.from(".cta-box", {
        scrollTrigger: {
          trigger: ref.current,
          start: "top 80%",
        },
        y: 30,
        opacity: 0,
        duration: 0.8,
        ease: "power2.out",
      });
    },
    { scope: ref },
  );

  return (
    <section
      id="contact"
      ref={ref}
      className="scroll-mt-24 py-20 md:py-28"
    >
      <div className="mx-auto max-w-4xl px-6">
        <div className="cta-box overflow-hidden rounded-3xl bg-gradient-to-br from-emerald-700 to-emerald-900 px-8 py-14 text-center text-white shadow-xl shadow-emerald-900/20 md:px-16 md:py-16">
          <h2 className="font-heading text-3xl font-bold tracking-tight md:text-4xl">
            Testez le dispositif dans votre établissement
          </h2>
          <p className="mx-auto mt-5 max-w-xl text-emerald-50/90 leading-relaxed">
            Vous souhaitez tester le dispositif dans une classe ou une cantine ?
            Nous pouvons vous accompagner dans une première installation pilote,
            adaptée à votre établissement et à vos usages.
          </p>

          <div className="mt-10 flex flex-wrap items-center justify-center gap-4">
            <ButtonLink
              href={`mailto:${CONTACT_EMAIL}?subject=Demande%20de%20d%C3%A9mo%20Cantaluz`}
              size="lg"
              className="gap-2 bg-white text-emerald-900 hover:bg-emerald-50"
            >
              <Mail className="size-4" />
              Demander une démo
            </ButtonLink>
            <ButtonLink
              href={`mailto:${CONTACT_EMAIL}?subject=Projet%20pilote%20Cantaluz`}
              size="lg"
              variant="outline"
              className="border-white/30 bg-transparent text-white hover:bg-white/10 hover:text-white"
            >
              Projet pilote
              <ArrowRight className="size-4" />
            </ButtonLink>
          </div>

          <p className="mt-8 flex items-center justify-center gap-2 text-sm text-emerald-100/80">
            <MapPin className="size-4" />
            Réseau Calendretta et établissements partenaires
          </p>
        </div>
      </div>
    </section>
  );
}
