"use client";

import Link from "next/link";
import { CookieSettingsLink } from "@/components/CookieBanner";
import { LEGAL } from "@/lib/legal";

export function LegalFooterLinks({ className = "" }: { className?: string }) {
  return (
    <nav
      className={`flex flex-wrap items-center justify-center gap-x-4 gap-y-2 text-xs text-muted-foreground ${className}`}
      aria-label="Liens légaux"
    >
      <Link href="/mentions-legales" className="hover:text-foreground">
        Mentions légales
      </Link>
      <span aria-hidden="true">·</span>
      <Link href="/politique-cookies" className="hover:text-foreground">
        Politique de cookies
      </Link>
      <span aria-hidden="true">·</span>
      <CookieSettingsLink className="hover:text-foreground" />
      <span aria-hidden="true">·</span>
      <a
        href={LEGAL.publisherUrl}
        target="_blank"
        rel="noopener noreferrer"
        className="hover:text-foreground"
      >
        {LEGAL.publisherUrl.replace("https://", "")}
      </a>
    </nav>
  );
}
