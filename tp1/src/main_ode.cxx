#include "ode.hxx"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

int main() {
  // Cas test: y' = 2 t y, y(0)=1, solution exacte y = exp(t^2)
  const auto f_test = [](double t, double y) { return 2.0 * t * y; };
  const OdeResult test_explicit = explicit_euler(0.0, 1.0, 100, 1.0, f_test);

  // Cas raide: y' = -50(y-cos(t)) = -50 y + 50 cos(t), y(0)=0
  const auto f_stiff = [](double t, double y) { return -50.0 * (y - std::cos(t)); };
  const auto rhs_stiff = [](double t) { return 50.0 * std::cos(t); };

  const int n_stiff = 40; // h=0.05
  const OdeResult stiff_explicit = explicit_euler(0.0, 2.0, n_stiff, 0.0, f_stiff);
  const OdeResult stiff_implicit = implicit_euler_linear(0.0, 2.0, n_stiff, 0.0, -50.0, rhs_stiff);

  std::ofstream out("tp1_ode_results.csv");
  out << "t,explicit_test,exact_test,explicit_stiff,implicit_stiff\n";

  const std::size_t n = test_explicit.t.size();
  for (std::size_t i = 0; i < n; ++i) {
    const double t = test_explicit.t[i];
    const double exact = std::exp(t * t);
    const std::size_t k = i * static_cast<std::size_t>(n_stiff) / (n - 1U);
    out << t << "," << test_explicit.y[i] << "," << exact << "," << stiff_explicit.y[k] << ","
        << stiff_implicit.y[k] << "\n";
  }
  out.close();

  const double y_end_num = test_explicit.y.back();
  const double y_end_exact = std::exp(1.0);
  std::cout << "Test Euler explicite: y(1) num=" << y_end_num << " exact=" << y_end_exact
            << " erreur=" << std::abs(y_end_num - y_end_exact) << '\n';

  std::cout << "Cas raide a t=2: explicit=" << stiff_explicit.y.back()
            << " implicit=" << stiff_implicit.y.back() << '\n';
  std::cout << "Resultats ecrits dans tp1_ode_results.csv\n";
  return EXIT_SUCCESS;
}
