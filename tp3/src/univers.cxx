#include "univers.hxx"

#include <cmath>

namespace {

constexpr double G = 1.0;
constexpr double SOFT = 1e-12;

} // namespace

Univers::Univers(int dimension, double dt) : dimension_(dimension), dt_(dt) {}

void Univers::add_particle(const Particule &p) {
  particles_.push_back(p);
}

std::size_t Univers::particle_count() const {
  return particles_.size();
}

const std::vector<Particule> &Univers::particles() const {
  return particles_;
}

std::vector<Particule> &Univers::particles() {
  return particles_;
}

Univers Univers::make_uniform_grid(int n_per_axis, double mass, const Vecteur &velocity, double cube_max) {
  Univers u(3, 1e-3);
  int id = 0;

  const double step = (n_per_axis > 1) ? (cube_max / static_cast<double>(n_per_axis - 1)) : 0.0;

  for (int i = 0; i < n_per_axis; ++i) {
    for (int j = 0; j < n_per_axis; ++j) {
      for (int k = 0; k < n_per_axis; ++k) {
        const Vecteur pos(i * step, j * step, k * step);
        u.add_particle(Particule(id, mass, pos, velocity));
        ++id;
      }
    }
  }
  return u;
}

void Univers::compute_forces_naive() {
  for (auto &p : particles_) {
    p.reset_force();
  }

  const std::size_t n = particles_.size();
  for (std::size_t i = 0; i < n; ++i) {
    Vecteur force_i(0.0, 0.0, 0.0);
    for (std::size_t j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      const Vecteur rij = particles_[j].position() - particles_[i].position();
      const double r2 = rij.norme2() + SOFT;
      const double r = std::sqrt(r2);
      const double coeff = G * particles_[i].masse() * particles_[j].masse() / (r2 * r);
      force_i += coeff * rij;
    }
    particles_[i].add_force(force_i);
  }
}

void Univers::compute_forces_half() {
  for (auto &p : particles_) {
    p.reset_force();
  }

  const std::size_t n = particles_.size();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i + 1; j < n; ++j) {
      const Vecteur rij = particles_[j].position() - particles_[i].position();
      const double r2 = rij.norme2() + SOFT;
      const double r = std::sqrt(r2);
      const double coeff = G * particles_[i].masse() * particles_[j].masse() / (r2 * r);
      const Vecteur fij = coeff * rij;
      particles_[i].add_force(fij);
      particles_[j].add_force(-1.0 * fij);
    }
  }
}

void Univers::advance(bool use_half_force) {
  if (use_half_force) {
    compute_forces_half();
  } else {
    compute_forces_naive();
  }

  for (auto &p : particles_) {
    const Vecteur acc = p.force() / p.masse();
    const Vecteur new_vel = p.vitesse() + dt_ * acc;
    const Vecteur new_pos = p.position() + dt_ * new_vel;
    p.set_vitesse(new_vel);
    p.set_position(new_pos);
  }

  (void)dimension_;
}
