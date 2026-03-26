#include "universe.hxx"

#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  const double epsilon = 1.0;
  const double sigma = 1.0;
  const double cutoff = 6.0;
  Universe universe(10.0, 10.0, cutoff, epsilon, sigma, 1e-3);

  std::ofstream out("tp4_lj_curve.csv");
  out << "r,potential\n";
  for (double r = 0.85; r <= 4.0; r += 0.01) {
    out << r << "," << universe.lennard_jones_potential(r) << "\n";
  }
  out.close();

  const double rmin = std::pow(2.0, 1.0 / 6.0) * sigma;
  std::cout << "Courbe ecrite dans tp4_lj_curve.csv\n";
  std::cout << "Minimum theorique autour de r = " << rmin << "\n";
  return 0;
}
