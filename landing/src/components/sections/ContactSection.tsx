"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ScrollTrigger } from "gsap/ScrollTrigger";
import { ButtonLink } from "@/components/ui/button-link";
import { Mail, ArrowRight } from "lucide-react";

gsap.registerPlugin(ScrollTrigger);


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
            Expérimentez Cantaluz avec votre classe
          </h2>
          <p className="mx-auto mt-5 max-w-xl text-emerald-50/90 leading-relaxed">
            Vous souhaitez tester le dispositif en conditions réelles ? Nous
            vous accompagnons dans une installation pilote — pour observer avec
            vos élèves comment un repère lumineux peut transformer la vie du
            groupe.
          </p>

          <div className="mt-10 flex flex-wrap items-center justify-center gap-4">
            <ButtonLink
              href={`mailto:contact@opteo-web.fr?subject=Demande%20de%20d%C3%A9mo%20Cantaluz`}
              size="lg"
              className="gap-2 bg-white text-emerald-900 hover:bg-emerald-50"
            >
              <Mail className="size-4" />
              Demander une démo
            </ButtonLink>
            <ButtonLink
              href={`mailto:contact@opteo-web.fr?subject=Projet%20pilote%20Cantaluz`}
              size="lg"
              variant="outline"
              className="border-white/30 bg-transparent text-white hover:bg-white/10 hover:text-white"
            >
              Projet pilote
              <ArrowRight className="size-4" />
            </ButtonLink>
          </div>

          <p className="mt-8 text-sm text-emerald-100/80">
            Projet conduit par{" "}
            <a
              href="https://opteo-web.fr"
              target="_blank"
              rel="noopener noreferrer"
              className="underline underline-offset-2 hover:text-white"
            >
              opteo-web.fr
            </a>
          </p>
        </div>
      </div>
    </section>
  );
}
