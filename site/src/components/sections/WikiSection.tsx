"use client";

import { useRef } from "react";
import { useGSAP } from "@gsap/react";
import gsap from "gsap";
import { ScrollTrigger } from "gsap/ScrollTrigger";
import { Badge } from "@/components/ui/badge";
import { ButtonLink } from "@/components/ui/button-link";
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { DOCS, PROJECT, REPO_TREE } from "@/lib/project";
import {
  BookOpen,
  ExternalLink,
  FileCode2,
  FolderTree,
  Code2,
  Terminal,
} from "lucide-react";

gsap.registerPlugin(ScrollTrigger);

export function WikiSection() {
  const sectionRef = useRef<HTMLElement>(null);

  useGSAP(
    () => {
      gsap.from(".wiki-card", {
        scrollTrigger: { trigger: sectionRef.current, start: "top 72%" },
        y: 40,
        opacity: 0,
        duration: 0.7,
        stagger: 0.08,
        ease: "power2.out",
      });
    },
    { scope: sectionRef },
  );

  return (
    <section
      id="wiki"
      ref={sectionRef}
      className="scroll-mt-24 border-t border-white/5 py-24 md:py-32"
    >
      <div className="mx-auto max-w-6xl px-6">
        <div className="mx-auto max-w-2xl text-center">
          <Badge variant="outline" className="border-violet-500/40 text-violet-400">
            Documentation · Open source
          </Badge>
          <h2 className="font-heading mt-4 text-3xl font-bold tracking-tight md:text-4xl">
            Wiki & dépôt GitHub
          </h2>
          <p className="mt-4 text-muted-foreground leading-relaxed">
            Projet ouvert : firmware Arduino, app web embarquée et sites de
            présentation. Clonez, explorez, adaptez — la doc vit dans le
            dépôt.
          </p>
        </div>

        <Card className="wiki-card mt-12 border-white/10 bg-gradient-to-br from-card/80 to-violet-500/5">
          <CardContent className="flex flex-col gap-6 p-6 sm:flex-row sm:items-center sm:justify-between">
            <div className="flex items-start gap-4">
              <div className="flex size-12 shrink-0 items-center justify-center rounded-xl bg-white/5 text-foreground">
                <Code2 className="size-6" />
              </div>
              <div>
                <p className="font-mono text-sm text-violet-300">{PROJECT.githubRepo}</p>
                <p className="mt-1 text-sm text-muted-foreground">
                  Firmware · app PROGMEM · docs · sites Next.js
                </p>
                <div className="mt-2 flex flex-wrap gap-2">
                  {PROJECT.stack.map((t) => (
                    <Badge key={t} variant="secondary" className="text-xs">
                      {t}
                    </Badge>
                  ))}
                </div>
              </div>
            </div>
            <ButtonLink
              href={PROJECT.githubUrl}
              target="_blank"
              rel="noopener noreferrer"
              className="shrink-0 gap-2"
            >
              Voir sur GitHub
              <ExternalLink className="size-4" />
            </ButtonLink>
          </CardContent>
        </Card>

        <div className="wiki-card mt-8 grid gap-6 lg:grid-cols-2">
          <Card className="border-white/10 bg-card/50">
            <CardHeader>
              <div className="flex items-center gap-2 text-emerald-400">
                <Terminal className="size-5" />
                <CardTitle className="text-lg">Quick start</CardTitle>
              </div>
              <CardDescription>
                Installation minimale — détails dans le README du dépôt.
              </CardDescription>
            </CardHeader>
            <CardContent>
              <pre className="overflow-x-auto rounded-lg border border-white/10 bg-black/40 p-4 font-mono text-xs leading-relaxed text-emerald-100/90">
{`git clone ${PROJECT.cloneUrl}
cd Cantaluz-Metric_Son/Main
# Arduino IDE : carte LOLIN(WEMOS) D1 R1
# Installer FastLED, ouvrir Main.ino
# Régler Config.h → téléverser`}
              </pre>
              <p className="mt-3 text-xs text-muted-foreground">
                Carte : <strong className="text-foreground">LOLIN(WEMOS) D1 R1</strong> —
                pas « Generic ESP8266 ». Moniteur série fermé en usage Wi-Fi.
              </p>
            </CardContent>
          </Card>

          <Card className="border-white/10 bg-card/50">
            <CardHeader>
              <div className="flex items-center gap-2 text-sky-400">
                <FolderTree className="size-5" />
                <CardTitle className="text-lg">Structure du dépôt</CardTitle>
              </div>
            </CardHeader>
            <CardContent>
              <ul className="space-y-2 font-mono text-xs text-muted-foreground">
                {REPO_TREE.map((line) => (
                  <li key={line} className="rounded-md border border-white/5 bg-black/20 px-3 py-2">
                    {line}
                  </li>
                ))}
              </ul>
            </CardContent>
          </Card>
        </div>

        <div className="mt-10">
          <div className="mb-6 flex items-center gap-2 text-muted-foreground">
            <BookOpen className="size-5" />
            <h3 className="font-heading text-lg font-semibold text-foreground">
              Fichiers de référence
            </h3>
          </div>
          <div className="grid gap-4 sm:grid-cols-2 lg:grid-cols-3">
            {DOCS.map((doc) => (
              <a
                key={doc.file}
                href={`${PROJECT.githubUrl}/blob/main/${doc.file}`}
                target="_blank"
                rel="noopener noreferrer"
                className="wiki-card group"
              >
                <Card className="h-full border-white/10 bg-card/40 transition-colors hover:border-violet-500/30 hover:bg-card/60">
                  <CardContent className="flex gap-3 p-4">
                    <FileCode2 className="mt-0.5 size-5 shrink-0 text-violet-400" />
                    <div>
                      <p className="font-mono text-sm text-foreground group-hover:text-violet-300">
                        {doc.file}
                      </p>
                      <p className="mt-1 text-xs font-medium">{doc.title}</p>
                      <p className="mt-1 text-xs text-muted-foreground leading-relaxed">
                        {doc.desc}
                      </p>
                    </div>
                  </CardContent>
                </Card>
              </a>
            ))}
          </div>
        </div>

        <p className="wiki-card mt-10 text-center text-sm text-muted-foreground">
          Projet conduit par{" "}
          <a
            href={PROJECT.publisherUrl}
            target="_blank"
            rel="noopener noreferrer"
            className="text-primary underline underline-offset-2"
          >
            opteo-web.fr
          </a>
          {" "}— contributions et retours bienvenus via GitHub Issues.
        </p>
      </div>
    </section>
  );
}
