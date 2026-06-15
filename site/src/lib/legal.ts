export const LEGAL = {
  siteName: "Cantaluz",
  publisherName: "Opteo Web",
  publisherUrl: "https://opteo-web.fr",
  publisherEmail: "contact@opteo-web.fr",
  hostName: "O2switch",
  hostUrl: "https://www.o2switch.fr",
  hostAddress: "Chemin des Pardiaux, 63000 Clermont-Ferrand, France",
  hostPhone: "04 44 44 60 40",
} as const;

export const COOKIE_CONSENT_KEY = "cantaluz-cookie-consent";

export type CookieConsent = {
  essential: true;
  analytics: boolean;
  updatedAt: string;
};

export function getDefaultConsent(analytics: boolean): CookieConsent {
  return {
    essential: true,
    analytics,
    updatedAt: new Date().toISOString(),
  };
}
