"use client";

import { Header } from "@/components/Header";
import { Footer } from "@/components/Footer";
import { HeroSection } from "@/components/sections/HeroSection";
import { ProblemeSection } from "@/components/sections/ProblemeSection";
import { SolutionSection } from "@/components/sections/SolutionSection";
import { CaracteristiquesSection } from "@/components/sections/CaracteristiquesSection";
import { PourquoiSection } from "@/components/sections/PourquoiSection";
import { BeneficesSection } from "@/components/sections/BeneficesSection";
import { PourQuiSection } from "@/components/sections/PourQuiSection";
import { ValeurSection } from "@/components/sections/ValeurSection";
import { ContactSection } from "@/components/sections/ContactSection";

export function MarketingPage() {
  return (
    <>
      <Header />
      <main>
        <HeroSection />
        <ProblemeSection />
        <SolutionSection />
        <CaracteristiquesSection />
        <PourquoiSection />
        <BeneficesSection />
        <PourQuiSection />
        <ValeurSection />
        <ContactSection />
      </main>
      <Footer />
    </>
  );
}
