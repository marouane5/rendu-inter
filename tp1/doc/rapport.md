# TP1 - Debogage et EDO

## Objectifs du TP

- Corriger un code C++ simple de calcul de trace.
- Mesurer les performances avec un outil de profiling.
- Proposer une version plus rapide.
- Implementer Euler explicite et Euler implicite pour des EDO du premier ordre.

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

Un executable dedie est fourni: `tp1_trace_profile`.

Compilation + profiling:

```bash
cmake -S . -B build
cmake --build build -j
./build/tp1/tp1_trace_profile 4000
gprof ./build/tp1/tp1_trace_profile gmon.out -b
```

Le gprof permet d identifier les zones de cout (remplissage et parcours de matrice).

### Question 4 - Modification qui ameliore les performances

Version optimisee fournie dans `tp1/src/main_trace_fast.cxx`:
- stockage contigu (`std::vector<double>`) au lieu de `vector<vector<...>>`
- meilleur acces cache pour la trace

Commande:

```bash
./build/tp1/tp1_trace_fast 4000
```

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

Le programme compare les deux methodes et ecrit les resultats dans `tp1_ode_results.csv`.

Commande:

```bash
./build/tp1/tp1_ode
```

## Justification des choix

- Code simple et lisible, sans mecanismes avances inutiles.
- Fonctions separees pour faciliter le test et la lecture.
- Variante optimisee minimale (memoire contigue) pour rester dans l esprit du TP.
- Sortie CSV pour verifier rapidement les resultats avec un tableur ou script.

## Synthese

Ce TP couvre les bases utiles pour la suite:
- correction de bugs C/C++
- mesure de performance
- premiere optimisation simple
- implementation de deux schemas numeriques standard pour EDO.

Le code reste volontairement simple pour etre facile a presenter et modifier.
