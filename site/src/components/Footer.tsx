import { Separator } from "@/components/ui/separator";
import { LegalFooterLinks } from "@/components/LegalFooterLinks";
import { PROJECT } from "@/lib/project";
import { Code2 } from "lucide-react";

export function Footer() {
  return (
    <footer className="border-t border-white/5 py-12">
      <div className="mx-auto max-w-6xl px-6 text-center">
        <p className="font-heading text-lg font-semibold">
          <span className="bg-gradient-to-r from-emerald-400 via-amber-400 to-rose-400 bg-clip-text text-transparent">
            Cantaluz
          </span>
        </p>
        <p className="mt-2 text-sm text-muted-foreground">
          La lumière qui répond au son · Wiki technique open source
        </p>
        <Separator className="my-6 bg-white/10" />
        <LegalFooterLinks className="mb-4" />
        <a
          href={PROJECT.githubUrl}
          target="_blank"
          rel="noopener noreferrer"
          className="inline-flex items-center gap-1.5 text-xs text-muted-foreground hover:text-foreground"
        >
          <Code2 className="size-3.5" />
          {PROJECT.githubRepo}
        </a>
        <p className="mt-3 text-xs text-muted-foreground">
          Projet par{" "}
          <a
            href={PROJECT.publisherUrl}
            target="_blank"
            rel="noopener noreferrer"
            className="underline underline-offset-2 hover:text-foreground"
          >
            opteo-web.fr
          </a>
        </p>
      </div>
    </footer>
  );
}
