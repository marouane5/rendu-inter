#include "trace_utils.hxx"

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::size_t n = 5U;
  if (argc > 1) {
    n = static_cast<std::size_t>(std::stoul(argv[1]));
  }

  Matrix matrix = initialize_matrix(n);
  fill_matrix(matrix);

  if (n <= 10U) {
    std::cout << "Matrix:\n";
    print_matrix(matrix);
  }

  const double sum = trace_matrix(matrix);
  std::cout << "Trace = " << sum << '\n';
  return EXIT_SUCCESS;
}
