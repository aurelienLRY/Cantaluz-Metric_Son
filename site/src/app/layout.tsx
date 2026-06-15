import type { Metadata } from "next";
import { DM_Sans, Fraunces } from "next/font/google";
import { CookieBanner } from "@/components/CookieBanner";
import "./globals.css";

const dmSans = DM_Sans({
  variable: "--font-sans",
  subsets: ["latin"],
});

const fraunces = Fraunces({
  variable: "--font-heading",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "Cantaluz — La lumière qui répond au son",
  description:
    "Projet pédagogique : ruban LED réactif au son, piloté par Wi-Fi. Outil d'accompagnement au calme pour la classe.",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html
      lang="fr"
      className={`${dmSans.variable} ${fraunces.variable} dark h-full scroll-smooth antialiased`}
    >
      <body className="min-h-full font-sans">
        {children}
        <CookieBanner />
      </body>
    </html>
  );
}
