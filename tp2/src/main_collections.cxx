#include "particle.hxx"

#include <chrono>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <vector>

namespace {

Particule make_particle(int id, std::mt19937 &gen) {
  std::uniform_real_distribution<double> pos_dist(0.0, 1.0);
  std::uniform_real_distribution<double> vel_dist(-1.0, 1.0);
  std::uniform_real_distribution<double> mass_dist(0.1, 10.0);
  return Particule(
    id,
    id % 4,
    mass_dist(gen),
    Vec2(pos_dist(gen), pos_dist(gen)),
    Vec2(vel_dist(gen), vel_dist(gen))
  );
}

double bench_vector(std::size_t n) {
  std::mt19937 gen(42);
  const auto start = std::chrono::steady_clock::now();
  std::vector<Particule> data;
  data.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    data.push_back(make_particle(static_cast<int>(i), gen));
  }
  volatile double sum = 0.0;
  for (const auto &p : data) {
    sum += p.masse();
  }
  (void)sum;
  const auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

double bench_deque(std::size_t n) {
  std::mt19937 gen(42);
  const auto start = std::chrono::steady_clock::now();
  std::deque<Particule> data;
  for (std::size_t i = 0; i < n; ++i) {
    data.push_back(make_particle(static_cast<int>(i), gen));
  }
  volatile double sum = 0.0;
  for (const auto &p : data) {
    sum += p.masse();
  }
  (void)sum;
  const auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

double bench_list(std::size_t n) {
  std::mt19937 gen(42);
  const auto start = std::chrono::steady_clock::now();
  std::list<Particule> data;
  for (std::size_t i = 0; i < n; ++i) {
    data.push_back(make_particle(static_cast<int>(i), gen));
  }
  volatile double sum = 0.0;
  for (const auto &p : data) {
    sum += p.masse();
  }
  (void)sum;
  const auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

double bench_set(std::size_t n) {
  std::mt19937 gen(42);
  const auto start = std::chrono::steady_clock::now();
  std::set<Particule> data;
  for (std::size_t i = 0; i < n; ++i) {
    data.insert(make_particle(static_cast<int>(i), gen));
  }
  volatile double sum = 0.0;
  for (const auto &p : data) {
    sum += p.masse();
  }
  (void)sum;
  const auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

} // namespace

int main() {
  const std::vector<std::size_t> sizes = {64, 128, 256, 512, 1024, 2048, 4096, 8192};

  std::ofstream out("tp2_collections.csv");
  out << "n,vector,deque,list,set\n";

  std::cout << std::left << std::setw(8) << "n" << std::setw(14) << "vector(s)" << std::setw(14)
            << "deque(s)" << std::setw(14) << "list(s)" << std::setw(14) << "set(s)" << "\n";

  for (std::size_t n : sizes) {
    const double tv = bench_vector(n);
    const double td = bench_deque(n);
    const double tl = bench_list(n);
    const double ts = bench_set(n);
    out << n << "," << tv << "," << td << "," << tl << "," << ts << "\n";
    std::cout << std::setw(8) << n << std::setw(14) << tv << std::setw(14) << td << std::setw(14) << tl
              << std::setw(14) << ts << "\n";
  }

  std::cout << "Resultats ecrits dans tp2_collections.csv\n";
  return 0;
}
