"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ScrollTrigger } from "gsap/ScrollTrigger";

gsap.registerPlugin(ScrollTrigger);

export function useScrollReveal(className = ".reveal") {
  const sectionRef = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      const els = sectionRef.current?.querySelectorAll(className);
      if (!els?.length) return;

      els.forEach((el, i) => {
        gsap.from(el, {
          scrollTrigger: {
            trigger: el,
            start: "top 88%",
            toggleActions: "play none none reverse",
          },
          y: 36,
          opacity: 0,
          duration: 0.75,
          delay: i * 0.06,
          ease: "power2.out",
        });
      });
    },
    { scope: sectionRef },
  );

  return sectionRef;
}
