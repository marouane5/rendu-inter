# TP2 - Particules et Stomer-Verlet

## Objectifs du TP

- Construire une classe `Particule`.
- Comparer des conteneurs standards C++ en perf.
- Implementer une simulation gravitationnelle avec Stomer-Verlet.
- Encapsuler les donnees avec methodes d acces.
- Garder uniquement les codes essentiels du sujet.

## Reponses aux questions

### Question 1 - Classe Particule

La classe est dans `tp2/include/particle.hxx`.

Champs implementes:
- position (`Vec2`)
- vitesse (`Vec2`)
- masse (`double`)
- identifiant (`int`)
- categorie (`int`)
- force (`Vec2`)

Les donnees sont privees et accessibles avec getters/setters.

### Question 2 - Collection de particules

Une collection de particules est creee dans `tp2/src/main_collections.cxx`.

Conteneurs utilises:
- `std::vector<Particule>`
- `std::deque<Particule>`
- `std::list<Particule>`
- `std::set<Particule>`

### Question 3 - Comparaison de performances

Programme: `tp2_collections`.

Tailles teste es:
- 64, 128, 256, 512, 1024, 2048, 4096, 8192

Sortie:
- affichage console
- fichier `tp2_collections.csv`

Observation attendue:
- `vector` est en general le plus rapide en insertion sequentielle + parcours
- `list` et `set` deviennent plus chers quand la taille augmente
- les differences deviennent visibles vers `n >= 1024` (selon machine)

### Question 4 - Implementation Stomer-Verlet

Programme: `tp2_verlet` dans `tp2/src/main_verlet.cxx`.

Le schema implemente:
1. calcul des forces gravitationnelles
2. mise a jour position
3. recalcul des forces
4. mise a jour vitesse

### Question 5 - Verification systeme propose

Systeme initialise:
- Soleil
- Terre
- Jupiter
- Halley

Parametres:
- `dt = 0.015`
- `t_end = 468.5`

Les positions sont ecrites dans `tp2_orbits.txt` (meme ligne par instant).

Commande:

```bash
./build/tp2/tp2_verlet 468.5 0.015 20
```

### Question 6 - Protection des donnees

La classe `Particule` utilise des attributs prives.

Ecriture controlee via:
- `set_position`
- `set_vitesse`
- `set_masse`
- `set_categorie`
- `reset_force` / `add_force`

Lecture via:
- `position`, `vitesse`, `masse`, `id`, `categorie`, `force`

## Justification de la solution

- Choix simple: 2D au lieu de 3D pour garder une simulation courte a lire.
- Types de base clairs (`Vec2`, `Particule`) sans mecanisme complexe.
- Separation de deux executables: benchmark d un cote, simulation de l autre.
- Sorties texte/csv pour faciliter validation et tracage.

## Synthese

Ce TP met en place une base propre pour les prochains labs:
- modelisation particulaire
- mesure de performance
- algorithme temporel de simulation
- encapsulation des donnees.

Le code reste volontairement simple et modifiable rapidement.
