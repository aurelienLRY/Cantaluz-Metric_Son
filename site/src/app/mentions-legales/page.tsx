import { LegalPageLayout } from "@/components/legal/LegalPageLayout";
import { LEGAL } from "@/lib/legal";

export const metadata = {
  title: `Mentions légales — ${LEGAL.siteName}`,
};

export default function MentionsLegalesPage() {
  return (
    <LegalPageLayout title="Mentions légales">
      <p>
        Conformément aux dispositions des articles 6-III et 19 de la Loi n°
        2004-575 du 21 juin 2004 pour la Confiance dans l&apos;économie
        numérique (LCEN), les présentes mentions légales s&apos;appliquent au
        site présentant le projet {LEGAL.siteName}.
      </p>

      <h2>Éditeur du site</h2>
      <p>
        <strong>{LEGAL.publisherName}</strong>
        <br />
        Site web :{" "}
        <a href={LEGAL.publisherUrl} target="_blank" rel="noopener noreferrer">
          {LEGAL.publisherUrl}
        </a>
        <br />
        Contact :{" "}
        <a href={`mailto:${LEGAL.publisherEmail}`}>{LEGAL.publisherEmail}</a>
        <br />
        Responsable de la publication : {LEGAL.publisherName}
      </p>

      <h2>Hébergement</h2>
      <p>
        Le site est hébergé par :
        <br />
        <strong>{LEGAL.hostName}</strong>
        <br />
        {LEGAL.hostAddress}
        <br />
        Site :{" "}
        <a href={LEGAL.hostUrl} target="_blank" rel="noopener noreferrer">
          {LEGAL.hostUrl}
        </a>
        <br />
        Téléphone : {LEGAL.hostPhone}
      </p>

      <h2>Propriété intellectuelle</h2>
      <p>
        L&apos;ensemble des contenus présents sur ce site (textes, visuels,
        structure, logo) est protégé par le droit de la propriété
        intellectuelle. Toute reproduction, représentation ou exploitation,
        totale ou partielle, sans autorisation préalable de{" "}
        {LEGAL.publisherName}, est interdite.
      </p>

      <h2>Données personnelles</h2>
      <p>
        Ce site vitrine ne collecte pas de données personnelles via des
        formulaires. Les préférences de cookies sont stockées localement dans
        votre navigateur. Pour en savoir plus, consultez la{" "}
        <a href="/politique-cookies">politique de cookies</a>.
      </p>

      <h2>Limitation de responsabilité</h2>
      <p>
        {LEGAL.publisherName} s&apos;efforce d&apos;assurer l&apos;exactitude des
        informations diffusées sur ce site. Toutefois, elle ne saurait être
        tenue responsable des omissions, inexactitudes ou d&apos;une
        indisponibilité temporaire du service.
      </p>

      <p className="text-xs">
        Dernière mise à jour : mai 2026
      </p>
    </LegalPageLayout>
  );
}
