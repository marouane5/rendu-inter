# Rendu intermediaire CPPMA

Ce depot contient 4 TP (`tp1`, `tp2`, `tp3`, `tp4`) avec:
- du code C++ simple
- un rapport `doc/rapport.md` dans chaque TP

## Compilation

```bash
cmake -S . -B build
cmake --build build -j
```

## Executables principaux

- `tp1_trace`, `tp1_trace_fast`, `tp1_trace_profile`, `tp1_ode`
- `tp2_collections`, `tp2_verlet`
- `tp3_lab3`, `tp3_test_vecteur`
- `tp4_lj_curve`, `tp4_collision`

## Tests

```bash
ctest --test-dir build --output-on-failure
```
