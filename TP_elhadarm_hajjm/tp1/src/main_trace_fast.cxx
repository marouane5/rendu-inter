#include "trace_utils.hxx"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::size_t n = 2000U;
  if (argc > 1) {
    n = static_cast<std::size_t>(std::stoul(argv[1]));
  }

  std::vector<double> matrix = initialize_matrix_flat(n);

  const auto t0 = std::chrono::steady_clock::now();
  fill_matrix_flat(matrix, n);
  const double sum = trace_matrix_flat(matrix, n);
  const auto t1 = std::chrono::steady_clock::now();

  const std::chrono::duration<double> elapsed = t1 - t0;
  std::cout << "Trace = " << sum << '\n';
  std::cout << "Elapsed = " << elapsed.count() << " s\n";
  return EXIT_SUCCESS;
}
