"use client";

import { useEffect, useState } from "react";
import { ButtonLink } from "@/components/ui/button-link";
import { cn } from "@/lib/utils";

const nav = [
  { href: "#probleme", label: "Le constat" },
  { href: "#solution", label: "La solution" },
  { href: "#caracteristiques", label: "Caractéristiques" },
  { href: "#benefices", label: "Bénéfices" },
  { href: "#pour-qui", label: "Pour qui" },
];

export function Header() {
  const [scrolled, setScrolled] = useState(false);

  useEffect(() => {
    const onScroll = () => setScrolled(window.scrollY > 16);
    onScroll();
    window.addEventListener("scroll", onScroll, { passive: true });
    return () => window.removeEventListener("scroll", onScroll);
  }, []);

  return (
    <header
      className={cn(
        "fixed inset-x-0 top-0 z-50 transition-all duration-300",
        scrolled
          ? "border-b border-border/60 bg-background/90 shadow-sm backdrop-blur-md"
          : "bg-transparent",
      )}
    >
      <div className="mx-auto flex max-w-6xl items-center justify-between px-6 py-4">
        <a href="#" className="font-heading text-xl font-semibold text-foreground">
          Cantaluz
        </a>
        <nav className="hidden items-center gap-8 text-sm text-muted-foreground md:flex">
          {nav.map((item) => (
            <a
              key={item.href}
              href={item.href}
              className="transition-colors hover:text-foreground"
            >
              {item.label}
            </a>
          ))}
        </nav>
        <ButtonLink href="#contact" size="sm">
          Demander une démo
        </ButtonLink>
      </div>
    </header>
  );
}
