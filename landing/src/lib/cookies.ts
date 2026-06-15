import {
  COOKIE_CONSENT_KEY,
  type CookieConsent,
  getDefaultConsent,
} from "./legal";

export function readCookieConsent(): CookieConsent | null {
  if (typeof window === "undefined") return null;
  try {
    const raw = localStorage.getItem(COOKIE_CONSENT_KEY);
    if (!raw) return null;
    return JSON.parse(raw) as CookieConsent;
  } catch {
    return null;
  }
}

export function writeCookieConsent(consent: CookieConsent) {
  localStorage.setItem(COOKIE_CONSENT_KEY, JSON.stringify(consent));
  window.dispatchEvent(new CustomEvent("cookie-consent-updated"));
}

export function acceptAllCookies() {
  writeCookieConsent(getDefaultConsent(true));
}

export function rejectOptionalCookies() {
  writeCookieConsent(getDefaultConsent(false));
}

export function hasConsentChoice(): boolean {
  return readCookieConsent() !== null;
}
