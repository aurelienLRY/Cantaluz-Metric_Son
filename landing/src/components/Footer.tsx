import { Separator } from "@/components/ui/separator";

export function Footer() {
  return (
    <footer className="border-t border-border/50 py-10">
      <div className="mx-auto max-w-6xl px-6 text-center">
        <p className="font-heading text-lg font-semibold text-foreground">
          Cantaluz
        </p>
        <p className="mt-2 text-sm text-muted-foreground">
          Vumètre pédagogique · Éducation au bruit · Autorégulation collective
        </p>
        <Separator className="my-6" />
        <p className="text-xs text-muted-foreground">
          Outil d&apos;accompagnement au calme — sans sanction, pour les classes
          et les cantines.
        </p>
      </div>
    </footer>
  );
}
