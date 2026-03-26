#pragma once

#include "particle.hxx"

#include <cstddef>
#include <vector>

class Univers {
public:
  Univers(int dimension, double dt = 1e-3);

  void add_particle(const Particule &p);
  std::size_t particle_count() const;

  const std::vector<Particule> &particles() const;
  std::vector<Particule> &particles();

  static Univers make_uniform_grid(int n_per_axis, double mass, const Vecteur &velocity, double cube_max = 1.0);

  void compute_forces_naive();
  void compute_forces_half();
  void advance(bool use_half_force);

private:
  int dimension_ = 3;
  double dt_ = 1e-3;
  std::vector<Particule> particles_;
};
