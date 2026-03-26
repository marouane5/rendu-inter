#include "vecteur.hxx"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

int main() {
  Vecteur a;
  assert(a[0] == 0.0 && a[1] == 0.0 && a[2] == 0.0);

  Vecteur b(1.0, 2.0, 3.0);
  Vecteur c(4.0, 5.0, 6.0);

  Vecteur s = b + c;
  assert(s[0] == 5.0 && s[1] == 7.0 && s[2] == 9.0);

  Vecteur d = c - b;
  assert(d[0] == 3.0 && d[1] == 3.0 && d[2] == 3.0);

  Vecteur p = 2.0 * b;
  assert(p[0] == 2.0 && p[1] == 4.0 && p[2] == 6.0);

  const double dot = Vecteur::dot(b, c);
  assert(dot == 32.0);

  const double n = Vecteur(3.0, 4.0, 0.0).norme();
  assert(std::abs(n - 5.0) < 1e-12);

  std::cout << "test_vecteur ok\n";
  return EXIT_SUCCESS;
}
