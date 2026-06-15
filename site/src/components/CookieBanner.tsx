"use client";

import { useCallback, useEffect, useState } from "react";
import Link from "next/link";
import { Button } from "@/components/ui/button";
import {
  acceptAllCookies,
  hasConsentChoice,
  readCookieConsent,
  rejectOptionalCookies,
  writeCookieConsent,
} from "@/lib/cookies";
import { getDefaultConsent } from "@/lib/legal";
import { Settings2, X } from "lucide-react";

export function CookieBanner() {
  const [visible, setVisible] = useState(false);
  const [manageOpen, setManageOpen] = useState(false);
  const [analytics, setAnalytics] = useState(false);

  const sync = useCallback(() => {
    const consent = readCookieConsent();
    setVisible(!consent);
    setAnalytics(consent?.analytics ?? false);
  }, []);

  useEffect(() => {
    sync();
    window.addEventListener("cookie-consent-updated", sync);
    window.addEventListener("open-cookie-settings", () => {
      setManageOpen(true);
      setVisible(true);
    });
    return () => {
      window.removeEventListener("cookie-consent-updated", sync);
    };
  }, [sync]);

  if (!visible) return null;

  const savePreferences = () => {
    writeCookieConsent(getDefaultConsent(analytics));
    setManageOpen(false);
    setVisible(false);
  };

  return (
    <div
      role="dialog"
      aria-label="Gestion des cookies"
      className="fixed inset-x-0 bottom-0 z-[100] border-t border-border bg-background/95 p-4 shadow-2xl backdrop-blur-md sm:p-6"
    >
      <div className="mx-auto max-w-4xl">
        {!manageOpen ? (
          <div className="flex flex-col gap-4 sm:flex-row sm:items-end sm:justify-between">
            <div className="max-w-2xl text-sm text-muted-foreground">
              <p className="font-medium text-foreground">Cookies et confidentialité</p>
              <p className="mt-1 leading-relaxed">
                Ce site utilise des cookies strictement nécessaires et, avec votre
                accord, des cookies de mesure d&apos;audience. Vous pouvez accepter,
                refuser ou personnaliser vos choix.{" "}
                <Link
                  href="/politique-cookies"
                  className="text-primary underline underline-offset-2"
                >
                  Politique de cookies
                </Link>
              </p>
            </div>
            <div className="flex flex-wrap gap-2">
              <Button
                size="sm"
                variant="outline"
                onClick={() => setManageOpen(true)}
                className="gap-1.5"
              >
                <Settings2 className="size-3.5" />
                Personnaliser
              </Button>
              <Button size="sm" variant="outline" onClick={rejectOptionalCookies}>
                Tout refuser
              </Button>
              <Button size="sm" onClick={acceptAllCookies}>
                Tout accepter
              </Button>
            </div>
          </div>
        ) : (
          <div className="space-y-4">
            <div className="flex items-center justify-between">
              <p className="font-medium">Préférences cookies</p>
              <button
                type="button"
                onClick={() => {
                  if (hasConsentChoice()) {
                    setManageOpen(false);
                    setVisible(false);
                  } else {
                    setManageOpen(false);
                  }
                }}
                className="rounded-md p-1 text-muted-foreground hover:text-foreground"
                aria-label="Fermer"
              >
                <X className="size-4" />
              </button>
            </div>

            <div className="space-y-3 rounded-lg border border-border p-4 text-sm">
              <div className="flex items-start justify-between gap-4">
                <div>
                  <p className="font-medium">Cookies essentiels</p>
                  <p className="mt-1 text-muted-foreground">
                    Nécessaires au fonctionnement du site et à la mémorisation de
                    vos préférences. Toujours actifs.
                  </p>
                </div>
                <span className="shrink-0 text-xs text-muted-foreground">Requis</span>
              </div>
              <div className="flex items-start justify-between gap-4 border-t border-border pt-3">
                <div>
                  <p className="font-medium">Mesure d&apos;audience</p>
                  <p className="mt-1 text-muted-foreground">
                    Cookies statistiques anonymes pour comprendre l&apos;usage du
                    site (non activés par défaut).
                  </p>
                </div>
                <label className="flex shrink-0 cursor-pointer items-center gap-2">
                  <input
                    type="checkbox"
                    checked={analytics}
                    onChange={(e) => setAnalytics(e.target.checked)}
                    className="size-4 accent-primary"
                  />
                  <span className="text-xs">Autoriser</span>
                </label>
              </div>
            </div>

            <div className="flex flex-wrap justify-end gap-2">
              <Button size="sm" variant="outline" onClick={rejectOptionalCookies}>
                Tout refuser
              </Button>
              <Button size="sm" onClick={savePreferences}>
                Enregistrer mes choix
              </Button>
            </div>
          </div>
        )}
      </div>
    </div>
  );
}

export function CookieSettingsLink({ className }: { className?: string }) {
  return (
    <button
      type="button"
      onClick={() =>
        window.dispatchEvent(new CustomEvent("open-cookie-settings"))
      }
      className={className}
    >
      Gérer les cookies
    </button>
  );
}
