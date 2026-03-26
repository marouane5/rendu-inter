#include "particle.hxx"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

constexpr double G = 1.0;
constexpr double SOFTENING = 1e-12;

std::vector<Particule> create_solar_system() {
  std::vector<Particule> particles;
  particles.emplace_back(0, 0, 1.0, Vec2(0.0, 0.0), Vec2(0.0, 0.0));            // Soleil
  particles.emplace_back(1, 1, 3.04e-6, Vec2(0.0, 1.0), Vec2(-1.0, 0.0));        // Terre
  particles.emplace_back(2, 1, 9.554e-4, Vec2(0.0, 5.36), Vec2(-0.425, 0.0));    // Jupiter
  particles.emplace_back(3, 2, 1.4e-14, Vec2(34.75, 0.0), Vec2(0.0, 0.0296));    // Halley
  return particles;
}

void reset_forces(std::vector<Particule> &particles) {
  for (auto &p : particles) {
    p.reset_force();
  }
}

void compute_gravity_forces(std::vector<Particule> &particles) {
  reset_forces(particles);
  const std::size_t n = particles.size();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i + 1; j < n; ++j) {
      const Vec2 rij = particles[j].position() - particles[i].position();
      const double r2 = rij.norm2() + SOFTENING;
      const double r = std::sqrt(r2);
      const double coeff = G * particles[i].masse() * particles[j].masse() / (r2 * r);
      const Vec2 fij = coeff * rij;
      particles[i].add_force(fij);
      particles[j].add_force(-fij);
    }
  }
}

void stormer_verlet_step(std::vector<Particule> &particles, double dt) {
  std::vector<Vec2> old_forces;
  old_forces.reserve(particles.size());
  for (const auto &p : particles) {
    old_forces.push_back(p.force());
  }

  for (auto &p : particles) {
    const Vec2 next_pos = p.position() + dt * p.vitesse() + (0.5 * dt * dt / p.masse()) * p.force();
    p.set_position(next_pos);
  }

  compute_gravity_forces(particles);

  for (std::size_t i = 0; i < particles.size(); ++i) {
    Particule &p = particles[i];
    const Vec2 next_vel = p.vitesse() + (0.5 * dt / p.masse()) * (old_forces[i] + p.force());
    p.set_vitesse(next_vel);
  }
}

void write_positions_line(std::ofstream &out, double t, const std::vector<Particule> &particles) {
  out << std::setprecision(12) << t;
  for (const auto &p : particles) {
    out << " " << p.position().x << " " << p.position().y;
  }
  out << "\n";
}

} // namespace

int main(int argc, char **argv) {
  double t_end = 468.5;
  double dt = 0.015;
  int output_every = 20;

  if (argc > 1) {
    t_end = std::stod(argv[1]);
  }
  if (argc > 2) {
    dt = std::stod(argv[2]);
  }
  if (argc > 3) {
    output_every = std::stoi(argv[3]);
  }

  std::vector<Particule> particles = create_solar_system();
  const std::vector<std::string> names = {"soleil", "terre", "jupiter", "halley"};

  std::ofstream out("tp2_orbits.txt");
  out << "t x_soleil y_soleil x_terre y_terre x_jupiter y_jupiter x_halley y_halley\n";

  compute_gravity_forces(particles);
  const int nsteps = static_cast<int>(std::ceil(t_end / dt));

  for (int step = 0; step <= nsteps; ++step) {
    const double t = step * dt;
    if (step % output_every == 0) {
      write_positions_line(out, t, particles);
    }
    if (step < nsteps) {
      stormer_verlet_step(particles, dt);
    }
  }

  out.close();

  std::cout << "Simulation finie. Fichier: tp2_orbits.txt\n";
  for (std::size_t i = 0; i < particles.size(); ++i) {
    std::cout << names[i] << " pos=(" << particles[i].position().x << ", " << particles[i].position().y
              << ")\n";
  }

  return EXIT_SUCCESS;
}
