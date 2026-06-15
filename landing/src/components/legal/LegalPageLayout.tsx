import Link from "next/link";
import { ButtonLink } from "@/components/ui/button-link";
import { LEGAL } from "@/lib/legal";
import { ArrowLeft } from "lucide-react";

export function LegalPageLayout({
  title,
  children,
}: {
  title: string;
  children: React.ReactNode;
}) {
  return (
    <div className="min-h-screen bg-background">
      <header className="border-b border-border/50">
        <div className="mx-auto flex max-w-3xl items-center justify-between px-6 py-4">
          <Link href="/" className="font-heading text-lg font-semibold">
            {LEGAL.siteName}
          </Link>
          <ButtonLink href="/" variant="ghost" size="sm" className="gap-1.5">
            <ArrowLeft className="size-3.5" />
            Accueil
          </ButtonLink>
        </div>
      </header>
      <main className="mx-auto max-w-3xl px-6 py-12">
        <h1 className="font-heading text-3xl font-bold tracking-tight">{title}</h1>
        <div className="prose-legal mt-8 space-y-6 text-sm leading-relaxed text-muted-foreground [&_h2]:mt-10 [&_h2]:text-base [&_h2]:font-semibold [&_h2]:text-foreground [&_a]:text-primary [&_a]:underline [&_strong]:text-foreground">
          {children}
        </div>
      </main>
    </div>
  );
}
