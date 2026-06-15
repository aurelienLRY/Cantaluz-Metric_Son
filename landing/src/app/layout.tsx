import type { Metadata } from "next";
import { Source_Sans_3, Source_Serif_4 } from "next/font/google";
import { CookieBanner } from "@/components/CookieBanner";
import "./globals.css";

const sourceSans = Source_Sans_3({
  variable: "--font-sans",
  subsets: ["latin"],
});

const sourceSerif = Source_Serif_4({
  variable: "--font-heading",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "Cantaluz — Repère sensoriel pour l'autorégulation en classe",
  description:
    "Un bandeau lumineux qui rend le bruit visible. Cantaluz accompagne les pédagogies Montessori et Freinet vers l'autonomie, la coopération et le respect du collectif.",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html
      lang="fr"
      className={`${sourceSans.variable} ${sourceSerif.variable} scroll-smooth antialiased`}
    >
      <body className="min-h-full font-sans">
        {children}
        <CookieBanner />
      </body>
    </html>
  );
}
