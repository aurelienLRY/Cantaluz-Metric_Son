import { LegalPageLayout } from "@/components/legal/LegalPageLayout";
import { LEGAL } from "@/lib/legal";

export const metadata = {
  title: `Politique de cookies — ${LEGAL.siteName}`,
};

export default function PolitiqueCookiesPage() {
  return (
    <LegalPageLayout title="Politique de cookies">
      <p>
        Cette politique explique comment le site {LEGAL.siteName}, édité par{" "}
        {LEGAL.publisherName}, utilise des cookies et technologies similaires
        conformément au Règlement général sur la protection des données (RGPD)
        et à la réglementation française.
      </p>

      <h2>Qu&apos;est-ce qu&apos;un cookie ?</h2>
      <p>
        Un cookie est un petit fichier texte déposé sur votre terminal
        (ordinateur, tablette, smartphone) lors de la consultation d&apos;un
        site. Des informations équivalentes peuvent être stockées dans le
        stockage local de votre navigateur (localStorage).
      </p>

      <h2>Cookies utilisés sur ce site</h2>

      <h2>1. Cookies strictement nécessaires</h2>
      <p>
        Ces cookies sont indispensables au bon fonctionnement du site. Ils
        permettent notamment de mémoriser vos préférences en matière de
        cookies. Ils ne peuvent pas être désactivés.
      </p>
      <ul className="list-disc space-y-1 pl-5">
        <li>
          <strong>cantaluz-cookie-consent</strong> (localStorage) — mémorise
          votre choix concernant les cookies · durée : 13 mois
        </li>
      </ul>

      <h2>2. Cookies de mesure d&apos;audience (optionnels)</h2>
      <p>
        Ces cookies ne sont déposés qu&apos;avec votre consentement explicite.
        Ils permettent de mesurer la fréquentation du site de manière
        anonymisée. Si vous refusez ces cookies, aucune mesure d&apos;audience
        n&apos;est activée.
      </p>

      <h2>Gérer vos préférences</h2>
      <p>
        Lors de votre première visite, une bannière vous permet d&apos;accepter,
        de refuser ou de personnaliser les cookies non essentiels. Vous pouvez
        modifier votre choix à tout moment via le lien « Gérer les cookies » en
        pied de page.
      </p>

      <h2>Contact</h2>
      <p>
        Pour toute question relative aux cookies ou à vos données personnelles,
        contactez {LEGAL.publisherName} :{" "}
        <a href={`mailto:${LEGAL.publisherEmail}`}>{LEGAL.publisherEmail}</a>
      </p>

      <p className="text-xs">
        Dernière mise à jour : mai 2026
      </p>
    </LegalPageLayout>
  );
}
