"use client";

import { useEffect, useState } from "react";
import { ButtonLink } from "@/components/ui/button-link";
import { PROJECT } from "@/lib/project";
import { cn } from "@/lib/utils";
import { Code2 } from "lucide-react";

const links = [
  { href: "#projet", label: "Projet" },
  { href: "#architecture", label: "Architecture" },
  { href: "#cablage", label: "Câblage" },
  { href: "#boitier", label: "Boîtier" },
  { href: "#application", label: "App" },
  { href: "#modes", label: "Modes" },
  { href: "#wiki", label: "Wiki" },
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
        <ul className="hidden items-center gap-5 text-sm text-muted-foreground lg:flex">
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
        <ButtonLink
          href={PROJECT.githubUrl}
          target="_blank"
          rel="noopener noreferrer"
          size="sm"
          variant="secondary"
          className="gap-1.5"
        >
          <Code2 className="size-3.5" />
          GitHub
        </ButtonLink>
      </nav>
    </header>
  );
}
