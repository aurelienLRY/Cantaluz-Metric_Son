import type { Metadata } from "next";
import { Source_Sans_3, Source_Serif_4 } from "next/font/google";
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
  title: "Cantaluz — Vumètre pédagogique pour l'école",
  description:
    "Rendez le bruit visible. Aidez les élèves à s'autoréguler en classe et en cantine grâce à un signal LED simple et immédiatement compréhensible.",
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
      <body className="min-h-full font-sans">{children}</body>
    </html>
  );
}
