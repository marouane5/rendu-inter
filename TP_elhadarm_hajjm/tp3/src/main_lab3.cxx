#include "univers.hxx"

#include <chrono>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace {

template <typename Container>
double bench_insert(std::size_t n) {
  const auto start = std::chrono::steady_clock::now();
  Container c;
  for (std::size_t i = 0; i < n; ++i) {
    c.push_back(static_cast<int>(i));
  }
  volatile std::size_t s = c.size();
  (void)s;
  const auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

double bench_forces(int n_per_axis, bool half, bool *skipped) {
  const std::size_t n = static_cast<std::size_t>(n_per_axis) * static_cast<std::size_t>(n_per_axis) *
                        static_cast<std::size_t>(n_per_axis);

  if (n > 12000) {
    *skipped = true;
    return 0.0;
  }

  Univers u = Univers::make_uniform_grid(n_per_axis, 1.0, Vecteur(0.0, 0.0, 0.0), 1.0);
  const auto start = std::chrono::steady_clock::now();
  if (half) {
    u.compute_forces_half();
  } else {
    u.compute_forces_naive();
  }
  const auto end = std::chrono::steady_clock::now();
  *skipped = false;
  return std::chrono::duration<double>(end - start).count();
}

} // namespace

int main(int argc, char **argv) {
  int k_max = 5;
  if (argc > 1) {
    k_max = std::stoi(argv[1]);
  }
  if (k_max < 3) {
    k_max = 3;
  }

  // Q6
  Univers base = Univers::make_uniform_grid(25, 1.0, Vecteur(0.1, 0.0, 0.0), 1.0);
  std::cout << "Univers (25)^3 cree, nb particules = " << base.particle_count() << "\n";

  // Q7
  const std::vector<std::size_t> sizes = {64, 128, 256, 512, 1024, 2048, 4096, 8192};
  std::ofstream insert_out("tp3_insert_bench.csv");
  insert_out << "n,vector,deque,list\n";

  std::cout << std::left << std::setw(8) << "n" << std::setw(14) << "vector(s)" << std::setw(14)
            << "deque(s)" << std::setw(14) << "list(s)" << "\n";
  for (std::size_t n : sizes) {
    const double tv = bench_insert<std::vector<int>>(n);
    const double td = bench_insert<std::deque<int>>(n);
    const double tl = bench_insert<std::list<int>>(n);
    insert_out << n << "," << tv << "," << td << "," << tl << "\n";
    std::cout << std::setw(8) << n << std::setw(14) << tv << std::setw(14) << td << std::setw(14) << tl
              << "\n";
  }

  // Q8 et Q9
  std::ofstream force_out("tp3_forces_bench.csv");
  force_out << "k,n,naive_s,half_s,status\n";

  for (int k = 3; k <= k_max; ++k) {
    const int n_axis = 1 << k;
    const std::size_t n = static_cast<std::size_t>(n_axis) * static_cast<std::size_t>(n_axis) *
                          static_cast<std::size_t>(n_axis);
    bool skip_naive = false;
    bool skip_half = false;
    const double naive = bench_forces(n_axis, false, &skip_naive);
    const double half = bench_forces(n_axis, true, &skip_half);
    const std::string status = (skip_naive || skip_half) ? "skipped_too_large" : "ok";
    force_out << k << "," << n << "," << naive << "," << half << "," << status << "\n";
    std::cout << "k=" << k << " n=" << n << " naive=" << naive << " half=" << half << " status=" << status
              << "\n";
  }

  std::cout << "Fichiers: tp3_insert_bench.csv et tp3_forces_bench.csv\n";
  return 0;
}
