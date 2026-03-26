#pragma once

#include "particle.hxx"

#include <cstddef>
#include <iosfwd>
#include <utility>
#include <vector>

class Universe {
public:
  Universe(double lx, double ly, double cutoff, double epsilon, double sigma, double dt);

  void add_particle(const Particle &p);
  std::size_t particle_count() const;

  void rebuild_cells();
  void compute_forces_lj();
  void step();

  void save_state_line(std::ostream &os, double t) const;
  double lennard_jones_potential(double r) const;

  int nx() const;
  int ny() const;

private:
  int cell_index(int ix, int iy) const;
  std::pair<int, int> to_cell(const Vec2 &p) const;
  void wrap(Vec2 &p) const;
  Vec2 minimum_image(Vec2 dr) const;

  double lx_;
  double ly_;
  double cutoff_;
  double cutoff2_;
  double epsilon_;
  double sigma_;
  double dt_;
  int nx_;
  int ny_;
  std::vector<Particle> particles_;
  std::vector<std::vector<std::size_t>> cells_;
};
