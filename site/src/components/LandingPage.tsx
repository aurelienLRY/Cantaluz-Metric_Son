"use client";

import { Hero } from "@/components/Hero";
import { Navbar } from "@/components/Navbar";
import { Footer } from "@/components/Footer";
import { ProjetSection } from "@/components/sections/ProjetSection";
import { ObjectifSection } from "@/components/sections/ObjectifSection";
import { BoitierSection } from "@/components/sections/BoitierSection";
import { AppSection } from "@/components/sections/AppSection";
import { ModesSection } from "@/components/sections/ModesSection";

export function LandingPage() {
  return (
    <>
      <Navbar />
      <main>
        <Hero />
        <ProjetSection />
        <ObjectifSection />
        <BoitierSection />
        <AppSection />
        <ModesSection />
      </main>
      <Footer />
    </>
  );
}
