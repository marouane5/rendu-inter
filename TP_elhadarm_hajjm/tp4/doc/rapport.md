# TP4 - Decoupage de l espace et Lennard-Jones

## Objectifs du TP

- Utiliser un potentiel de Lennard-Jones.
- Mettre en place un univers avec contraintes physiques.
- Ajouter un maillage en cellules pour reduire le cout.
- Mettre a jour les cellules a chaque iteration.
- Simuler la collision de deux objets.
- Garder uniquement les codes essentiels demandes.

## Reponses aux questions

### Question 1 - Courbe du potentiel Lennard-Jones

Executable:
- `tp4_lj_curve` (`tp4/src/main_lj_curve.cxx`)

Sortie:
- `tp4_lj_curve.csv` avec colonnes `r,potential`

Remarque:
- minimum du potentiel proche de `r = 2^(1/6) * sigma`
- avec `epsilon=1`, `sigma=1`

### Question 2 - Creation classe Univers

Classe creee:
- `tp4/include/universe.hxx`
- `tp4/src/universe.cxx`

Attributs principaux:
- dimensions `lx, ly`
- rayon de coupe `cutoff`
- constantes `epsilon, sigma`
- pas de temps `dt`
- particules
- grille de cellules

### Question 3 - Elements de grille dans Univers

Ajouts dans `Universe`:
- nombre de cellules `nx=floor(lx/cutoff)`, `ny=floor(ly/cutoff)`
- tableau `cells` (liste des indices de particules par cellule)
- fonction `rebuild_cells()` pour initialiser / mettre a jour

Voisinage pris en compte:
- 3x3 cellules en 2D autour de chaque cellule

### Question 4 - Calcul de force avec approche cellules

Implementation:
- `compute_forces_lj()`

Principe:
- calcul uniquement dans la cellule courante et cellules voisines
- filtrage par rayon de coupe `r <= cutoff`
- exploitation de la symetrie des paires (une seule fois par paire)

### Question 5 - Mise a jour des cellules

Implementation:
- `rebuild_cells()`

Utilisation:
- appelee avant et apres chaque pas de temps (`step()`)
- repositionne chaque particule dans sa cellule logique

### Question 6 - Simulation collision

Executable:
- `tp4_collision` (`tp4/src/main_collision.cxx`)

Parametres utilises:
- `L1=250`, `L2=40`
- `epsilon=5`, `sigma=1`
- `m=1`
- vitesse initiale bloc rouge `v=(0,10)`
- `N1=1600` (40x40), `N2=6400` (160x40)
- `rcut=2.5*sigma`
- `dt=0.00005`
- simulation jusque `t=19.5`

Sortie:
- `tp4_collision.txt` (etat periodique du systeme)

## Justification de la solution

- Choix volontairement simple en 2D pour rester lisible.
- Grille en cellules pour limiter le nombre de paires comparees.
- Conditions periodiques simples pour garder les particules dans le domaine.
- Sauvegarde texte exploitable pour tracage externe.

## Synthese

Ce TP ajoute un vrai passage a l echelle:
- interaction Lennard-Jones
- maillage spatial
- mise a jour dynamique des cellules
- simulation de collision avec un grand nombre de particules.

La solution reste simple, modulaire, et facile a presenter.
