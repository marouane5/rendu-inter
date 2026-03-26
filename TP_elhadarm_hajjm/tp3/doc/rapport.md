# TP3 - Operateurs, Vecteur, Univers

## Objectifs du TP

- Remplacer les donnees vectorielles brutes par une classe `Vecteur`.
- Ajouter des operateurs utiles et des tests.
- Integrer `Vecteur` dans `Particule`.
- Construire une classe `Univers` pour stocker et faire evoluer les particules.
- Mesurer les performances insertion et interactions.
- Garder uniquement les elements essentiels du sujet.

## Reponses aux questions

### Question 1 - Classe Vecteur 3D

Classe `Vecteur` creee dans `tp3/include/vecteur.hxx`.

Dimension:
- 3 composantes (`x,y,z`)

### Question 2 - Constructeurs et operateurs

Operateurs implementes:
- `+`, `-`, `*` scalaire, `/` scalaire
- `+=`, `-=`, `*=`
- acces `operator[]`
- `dot`, `norme`, `norme2`
- affichage `operator<<`

La classe est autonome (pas de dependance externe).

### Question 3 - Tests

Test unitaire:
- `tp3/test/test_vecteur.cxx`

Points verifies:
- constructeur par defaut
- somme / difference
- produit scalaire
- norme

### Question 4 - Modification de Particule

`Particule` utilise maintenant `Vecteur` pour:
- position
- vitesse
- force

Fichier: `tp3/include/particle.hxx`.

### Question 5 - Classe Univers

Classe `Univers` implementee dans:
- `tp3/include/univers.hxx`
- `tp3/src/univers.cxx`

Fonctions:
- stocker la collection de particules
- generer une grille uniforme
- calculer les forces (version naive et version optimisee)
- avancer les particules dans le temps

### Question 6 - Univers avec (25)^3 particules

Cree dans `tp3/src/main_lab3.cxx`:
- `Univers::make_uniform_grid(25, ...)`
- positions uniformes dans `[0,1]^3`

### Question 7 - Performance insertion

Benchmark insertion:
- `vector`, `deque`, `list`
- tailles de 64 a 8192

Sortie:
- console
- `tp3_insert_bench.csv`

### Question 8 - Performance calcul interactions

Benchmark calcul des forces:
- tailles `(2^k)^3` avec `k=3..k_max`
- fichier `tp3_forces_bench.csv`

Par securite de temps de calcul, les tres gros cas sont ignores (`status=skipped_too_large`).

### Question 9 - Modification simple pour diviser le temps par 2

Modification implementee:
- passer de la double boucle `i != j` (naive) a la boucle `i < j` avec symetrie des forces

Effet:
- nombre de paires presque divise par 2
- meme resultat physique (force opposee appliquee sur la deuxieme particule)

### Question 10 - Autres simplifications possibles

Simplifications simples proposees:
- rayon de coupure pour ignorer les interactions lointaines
- maillage spatial (cellules) pour limiter les paires
- precision reduite (`float`) si acceptable
- mise a jour moins frequente de certaines sorties debug

## Justification des choix

- Classe `Vecteur` courte pour bien voir les operateurs.
- Tests minimaux mais directs pour valider chaque methode importante.
- Deux versions de force (`naive` et `half`) pour comparer clairement les couts.
- Fichiers CSV pour faciliter la validation.

## Synthese

Ce TP prepare le passage vers une simulation plus grande:
- structures plus propres (`Vecteur`, `Particule`, `Univers`)
- mesure des couts
- premiere optimisation algorithmique simple mais efficace.
