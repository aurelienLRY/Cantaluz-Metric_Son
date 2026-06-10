"use client";

import { useEffect, useState } from "react";
import { ButtonLink } from "@/components/ui/button-link";
import { cn } from "@/lib/utils";

const links = [
  { href: "#projet", label: "Projet" },
  { href: "#objectif", label: "Objectifs" },
  { href: "#boitier", label: "Boîtier" },
  { href: "#application", label: "Application" },
  { href: "#modes", label: "Modes" },
];

export function Navbar() {
  const [scrolled, setScrolled] = useState(false);

  useEffect(() => {
    const onScroll = () => setScrolled(window.scrollY > 24);
    onScroll();
    window.addEventListener("scroll", onScroll, { passive: true });
    return () => window.removeEventListener("scroll", onScroll);
  }, []);

  return (
    <header
      className={cn(
        "fixed inset-x-0 top-0 z-50 transition-all duration-300",
        scrolled
          ? "border-b border-white/10 bg-background/80 backdrop-blur-md"
          : "bg-transparent",
      )}
    >
      <nav className="mx-auto flex max-w-6xl items-center justify-between px-6 py-4">
        <a href="#" className="font-heading text-lg font-semibold tracking-tight">
          <span className="bg-gradient-to-r from-emerald-400 via-amber-400 to-rose-400 bg-clip-text text-transparent">
            Cantaluz
          </span>
        </a>
        <ul className="hidden items-center gap-6 text-sm text-muted-foreground md:flex">
          {links.map((link) => (
            <li key={link.href}>
              <a
                href={link.href}
                className="transition-colors hover:text-foreground"
              >
                {link.label}
              </a>
            </li>
          ))}
        </ul>
        <ButtonLink href="#application" size="sm" variant="secondary">
          Voir l&apos;app
        </ButtonLink>
      </nav>
    </header>
  );
}
