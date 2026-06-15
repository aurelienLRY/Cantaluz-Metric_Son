import { Separator } from "@/components/ui/separator";
import { LegalFooterLinks } from "@/components/LegalFooterLinks";
import { LEGAL } from "@/lib/legal";

export function Footer() {
  return (
    <footer className="border-t border-border/50 py-10">
      <div className="mx-auto max-w-6xl px-6 text-center">
        <p className="font-heading text-lg font-semibold text-foreground">
          Cantaluz
        </p>
        <p className="mt-2 text-sm text-muted-foreground">
          Matériel concret · Autonomie · Coopération · Pédagogies actives
        </p>
        <Separator className="my-6" />
        <LegalFooterLinks className="mb-4" />
        <p className="text-xs text-muted-foreground">
          Projet conduit par{" "}
          <a
            href={LEGAL.publisherUrl}
            target="_blank"
            rel="noopener noreferrer"
            className="underline underline-offset-2 hover:text-foreground"
          >
            {LEGAL.publisherUrl.replace("https://", "")}
          </a>
          {" · "}Hébergé par {LEGAL.hostName}
        </p>
      </div>
    </footer>
  );
}
