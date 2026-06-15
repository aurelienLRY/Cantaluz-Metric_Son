"use client";

import { Hero } from "@/components/Hero";
import { Navbar } from "@/components/Navbar";
import { Footer } from "@/components/Footer";
import { ProjetSection } from "@/components/sections/ProjetSection";
import { ObjectifSection } from "@/components/sections/ObjectifSection";
import { CablageSection } from "@/components/sections/CablageSection";
import { BoitierSection } from "@/components/sections/BoitierSection";
import { AppSection } from "@/components/sections/AppSection";
import { ModesSection } from "@/components/sections/ModesSection";
import { WikiSection } from "@/components/sections/WikiSection";

export function LandingPage() {
  return (
    <>
      <Navbar />
      <main>
        <Hero />
        <ProjetSection />
        <ObjectifSection />
        <CablageSection />
        <BoitierSection />
        <AppSection />
        <ModesSection />
        <WikiSection />
      </main>
      <Footer />
    </>
  );
}
