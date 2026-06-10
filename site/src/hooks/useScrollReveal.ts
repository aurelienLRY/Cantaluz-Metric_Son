"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ScrollTrigger } from "gsap/ScrollTrigger";

gsap.registerPlugin(ScrollTrigger);

type ScrollRevealOptions = {
  textSelector?: string;
  mediaSelector?: string;
  mediaFromX?: number;
  scrub?: boolean | number;
};

export function useScrollReveal(options: ScrollRevealOptions = {}) {
  const {
    textSelector = ".reveal-text",
    mediaSelector = ".reveal-media",
    mediaFromX = 60,
    scrub = false,
  } = options;

  const sectionRef = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      const section = sectionRef.current;
      if (!section) return;

      const textEls = section.querySelectorAll(textSelector);
      const mediaEls = section.querySelectorAll(mediaSelector);

      textEls.forEach((el, i) => {
        gsap.from(el, {
          scrollTrigger: {
            trigger: el,
            start: "top 85%",
            toggleActions: "play none none reverse",
          },
          y: 48,
          opacity: 0,
          duration: 0.9,
          delay: i * 0.08,
          ease: "power3.out",
        });
      });

      mediaEls.forEach((el) => {
        gsap.from(el, {
          scrollTrigger: {
            trigger: section,
            start: "top 70%",
            end: "bottom 30%",
            scrub: scrub === false ? false : scrub === true ? 1 : scrub,
            toggleActions: scrub ? undefined : "play none none reverse",
          },
          x: mediaFromX,
          opacity: scrub ? 0.5 : 0,
          scale: 0.92,
          duration: scrub ? undefined : 1.1,
          ease: "power2.out",
        });
      });
    },
    { scope: sectionRef },
  );

  return sectionRef;
}
