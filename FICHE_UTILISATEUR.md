# Cantaluz — Fiche utilisateur (format A4)

> **Cantaluz** — *La lumière qui répond au son*  
> Outil d'accompagnement au calme · projet pédagogique · *canta* (chanter) + *luz* (lumière)

---

## Le projet en bref

Cantaluz est un **ruban LED** qui réagit au **son** de la classe (voix, bruit, musique).  
Un **micro** mesure l'ambiance ; le ruban affiche une **barre lumineuse** :

- **Hauteur** = intensité du son (peu de LED au calme, plus de LED si c'est bruyant).
- **Couleurs sur le bandeau** = du **vert** (début du ruban) à l'**orange**, puis au **rouge** (fin du ruban), selon la position le long du bandeau.

L'enseignant peut **choisir le mode** et **ajuster les réglages** depuis un **téléphone**, sans câble, via le Wi-Fi intégré.

---

## Mise en marche

1. Brancher l'**alimentation 5 V** du ruban LED et la **carte** (câble USB ou alim prévue).
2. Appuyer sur le **bouton marche / arrêt** de l'appareil.
3. Attendre quelques secondes : le ruban et le Wi-Fi se préparent (voir ci-dessous).

Pour **éteindre** : même bouton. Au prochain allumage, le mode **Flash** reprend par défaut (sauf réglage technique dans le code).

---

## Au démarrage (séquence automatique)

Dès l'allumage, **aucune manipulation n'est nécessaire**. L'appareil enchaîne :

| Étape | Ce que vous voyez |
|-------|-------------------|
| 1 | Ruban **bleu** un instant (signal « je démarre »). |
| 2 | Animation **verte** : la lumière **monte** le long du ruban puis **redescend** (*effet « na-na-na »* visuel). |
| 3 | Le ruban passe en **mode d'écoute** : quelques LED vertes au silence, le ruban réagit au son. |
| 4 | Le réseau Wi-Fi **`Cantaluz`** devient disponible (LED bleue sur la carte = Wi-Fi actif). |

Ensuite l'appareil fonctionne en **mode Flash** (mode par défaut).

> **Conseil** : ne pas brancher le moniteur série de l'ordinateur en usage normal — cela peut gêner le Wi-Fi.

---

## Les trois modes

Choisir un mode dans l'app (onglet **Dashboard** → carte **Mode**). Le changement est **immédiat** sur le ruban.

### 1. Flash *(mode par défaut au démarrage)*

**Comportement**

- Barre lumineuse **réactive** au son.
- Couleurs **vert → orange → rouge** le long du ruban selon la hauteur de la barre.
- À chaque **montée d'intensité** (calme → plus animé → très bruyant) : **flashs bleus** sur tout le ruban.

**Cas d'usage**

- Suivre **visuellement** le niveau sonore de la classe.
- **Signaler** les pics de bruit (flash bleu = palier dépassé).
- Séance normale, atelier, temps d'échange **quand on veut un retour net** sur les dépassements.

---

### 2. Standard

**Comportement**

- Même principe de **barre** et de **couleurs sur le ruban**.
- Montée et descente **plus douces**, **sans flash bleu**.
- Ambiance plus **fluide**, moins « nerveuse ».

**Cas d'usage**

- Travail silencieux ou **semi-silencieux** prolongé.
- Lecture, écriture, activité calme où la lumière **accompagne** sans alerter brutalement.
- Classe déjà habituée au ruban ; le son reste visible sans les flashs.

---

### 3. Méditation guidée

**Comportement**

- Le **micro est ignoré** pendant la séance.
- Exercice de **respiration** guidé par la lumière :
  - **Cyan** = inspire  
  - **Ambre** = retiens (poumons pleins)  
  - **Magenta** = expire  
  - **Lavande** = bloque l'air (fin de cycle)  
- Les LED s'allument **une par une**, toujours dans le **même sens** sur le ruban.
- Durée au choix : **2 min**, **5 min** ou **10 min**, puis bouton **Démarrer** (compte à rebours 5 s, puis chrono).

**Cas d'usage**

- Classe **agitée** : pause respiration collective.
- Après la récréation, avant une évaluation, ou en fin de journée.
- Rituel de **retour au calme** guidé par le ruban.

---

## Mode au démarrage

| | |
|---|---|
| **Mode par défaut** | **Flash** |
| **Après extinction / rallumage** | **Flash** à nouveau |
| **Changer de mode** | Via l'app (reste actif jusqu'au prochain redémarrage de l'appareil) |

---

## Pour changer de mode ou régler l'appareil

Vous devez utiliser un **smartphone** (ou tablette) connecté au Wi-Fi de Cantaluz.

### Étape 1 — Se connecter au Wi-Fi Cantaluz

| | |
|---|---|
| **Réseau** | `Cantaluz` |
| **Mot de passe** | `cantaluz1` |

- Sur **Android / iPhone** : si un message « pas d'Internet » apparaît, **rester connecté** au réseau Cantaluz (ne pas repasser en 4G).
- Préférer **Chrome** si la page ne s'ouvre pas toute seule.

### Étape 2 — Ouvrir l'application Cantaluz

- La page peut s'ouvrir **automatiquement** (portail captif).
- Sinon, saisir dans le navigateur : **`http://cantaluz.local`** ou **`http://192.168.4.1`**

### Étape 3 — Utiliser l'app

| Onglet | Contenu |
|--------|---------|
| **Dashboard** | Graphique d'ambiance (30 s), barre de niveau, **choix du mode** (Flash / Standard / Méditation guidée). En Méditation : durée 2 / 5 / 10 min, **Démarrer** / **Arrêter**. |
| **Réglages** | Curseurs + bouton **i** (aide) et **↺** (valeur d'origine). *Grisé en mode Méditation.* |

| Réglage | À quoi ça sert |
|---------|----------------|
| **Sensibilité** | Plus **bas** = ruban stable au silence. Plus **haut** = réaction plus forte à la voix. |
| **Zone calme** | Seuil en dessous duquel le ruban reste surtout **vert** (paliers / flashs). |
| **Zone animée** | Seuil de passage vers **orange** puis **rouge**. |
| **Luminosité** | Intensité globale du ruban. |
| **Montée de la barre** | Vitesse à laquelle la barre monte quand le son augmente. |

Les réglages s'appliquent **tout de suite**. Ils sont **perdus au redémarrage** de l'appareil (retour aux valeurs par défaut du firmware).

---

## Lecture rapide du ruban (modes Flash et Standard)

```
[Début du ruban]  ████████░░░░░░░░░░░░░░░░  [Fin]
                  vert    orange      rouge
                  ↑ peu de LED = calme
                  ↑ beaucoup de LED = bruyant
```

- **Flash bleu** (mode Flash uniquement) = la classe vient de passer un **palier** sonore vers le haut.

---

## Dépannage express

| Problème | Piste |
|----------|--------|
| Pas de Wi-Fi `Cantaluz` | Vérifier alimentation USB ; attendre 10 s après l'allumage ; LED bleue carte allumée ? |
| Page web ne s'ouvre pas | Chrome → `192.168.4.1` ; désactiver « données mobiles automatiques ». |
| Ruban bouge tout seul | Réglages → baisser **Sensibilité** (essayer 0–10). |
| Trop de rouge / flashs | Baisser **Sensibilité** ; augmenter **Zone calme** et **Zone animée**. |
| Méditation ne démarre pas | Choisir d'abord le mode **Méditation guidée**, puis **2 / 5 / 10 min**, puis **Démarrer**. |

---

## Rappels sécurité & matériel

- Ruban LED alimenté en **5 V** (alimentation adaptée, **masse commune** avec la carte).
- Ne pas regarder le ruban de trop près en pleine luminosité prolongée.
- Réservé à un **usage scolaire** avec adulte référent.

---

*Cantaluz — école occitane · document utilisateur · à imprimer en A4 (portrait)*
