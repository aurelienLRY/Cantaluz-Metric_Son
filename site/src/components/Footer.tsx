import { Separator } from "@/components/ui/separator";

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
          La lumière qui répond au son · Outil d&apos;accompagnement au calme
        </p>
        <Separator className="my-6 bg-white/10" />
        <p className="text-xs text-muted-foreground">
          Projet pédagogique · WeMos D1 · ESP8266 · WS2812B · MAX4466
        </p>
      </div>
    </footer>
  );
}
