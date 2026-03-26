# TP1 - Debogage et EDO

## Objectifs du TP

- Corriger un code C++ simple de calcul de trace.
- Implementer Euler explicite et Euler implicite pour des EDO du premier ordre.
- Rester sur une base minimale: 2 codes (`trace corrige` et `ode`).

## Partie 1 - Debogage

### Question 1 - Problemes identifies

Problemes vus dans le code initial:
- oubli de `std::cin` et include manquant
- declaration `fill_vectors` differente de la definition `fill_vector`
- type de retour faux dans `trace` (retourne pointeur vers variable locale)
- type de retour faux dans `fill_vector` (retourne `&vec` au lieu de `vec`)
- indices faux (boucles commencent a 1, et vont jusqu a `<= n`)
- erreur de type avec `calloc` et cast C vers C++
- affichage de la trace avec un pointeur au lieu d une valeur

### Question 2 - Corrections faites

Corrections implementees dans `tp1/src/trace_utils.cxx` et `tp1/src/main_trace.cxx`:
- utilisation de `std::vector<std::vector<double>>` pour une gestion memoire simple
- boucles corrigees de `0` a `n-1`
- fonction `trace_matrix` qui retourne un `double`
- remplissage aleatoire stable avec seed
- affichage conditionnel de la matrice (seulement pour petite taille)

Commande:

```bash
./build/tp1/tp1_trace 5
```

### Question 3 - Profiling

Le profiling se fait sur le code `tp1_trace` (pas de code supplementaire).
Exemple simple:

```bash
g++ -std=c++17 -pg tp1/src/main_trace.cxx tp1/src/trace_utils.cxx -I tp1/include -o tp1_trace_pg
./tp1_trace_pg 4000
gprof ./tp1_trace_pg gmon.out -b
```

Le gprof permet d identifier les zones de cout (remplissage et parcours de matrice).

### Question 4 - Modification qui ameliore les performances

Proposition simple (sans ajouter un 3eme code):
- passer a un stockage contigu (`std::vector<double>`)
- limiter les affichages console pour les grandes tailles
- eviter de recalculer des tailles dans les boucles

## Partie 2 - Resolution d EDO

### Euler explicite (cas test)

Equation test:
- `y' = 2 t y`
- `y(0)=1`
- solution exacte: `y(t)=exp(t^2)`

Implementation:
- `explicit_euler(...)` dans `tp1/src/ode.cxx`
- programme `tp1_ode` dans `tp1/src/main_ode.cxx`

### Euler implicite (cas raide)

Equation raide:
- `y' = -50(y-cos(t))`
- `y(0)=0`

Implementations:
- Euler explicite general
- Euler implicite lineaire avec formule fermee

Commande:

```bash
./build/tp1/tp1_ode
```

## Justification des choix

- Code simple et lisible, sans mecanismes avances inutiles.
- Fonctions separees pour faciliter le test et la lecture.
- Perimetre volontairement minimal: seulement `tp1_trace` et `tp1_ode`.

## Synthese

Ce TP couvre les bases utiles pour la suite:
- correction de bugs C/C++
- mesure de performance (sur le code corrige)
- implementation de deux schemas numeriques standard pour EDO.

Le code reste volontairement simple pour etre facile a presenter et modifier.
