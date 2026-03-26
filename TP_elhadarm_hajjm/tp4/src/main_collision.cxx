#include "universe.hxx"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace {

int add_block(
  Universe &u,
  int id_start,
  int type,
  int nx,
  int ny,
  const Vec2 &origin,
  double spacing,
  double mass,
  const Vec2 &velocity
) {
  int id = id_start;
  for (int i = 0; i < nx; ++i) {
    for (int j = 0; j < ny; ++j) {
      const Vec2 pos(origin.x + i * spacing, origin.y + j * spacing);
      u.add_particle(Particle(id, type, mass, pos, velocity));
      ++id;
    }
  }
  return id;
}

} // namespace

int main(int argc, char **argv) {
  const double lx = 250.0;
  const double ly = 40.0;
  const double epsilon = 5.0;
  const double sigma = 1.0;
  const double mass = 1.0;
  const Vec2 v_red(0.0, 10.0);
  const int n1 = 1600; // 40x40
  const int n2 = 6400; // 160x40
  const double cutoff = 2.5 * sigma;
  const double dt = 0.00005;
  double t_end = 19.5;
  int save_every = 500;

  if (argc > 1) {
    t_end = std::stod(argv[1]);
  }
  if (argc > 2) {
    save_every = std::stoi(argv[2]);
  }

  Universe u(lx, ly, cutoff, epsilon, sigma, dt);
  const double spacing = std::pow(2.0, 1.0 / 6.0) * sigma;

  int next_id = 0;
  next_id = add_block(u, next_id, 1, 40, 40, Vec2(10.0, 0.5), spacing, mass, v_red);
  next_id = add_block(u, next_id, 2, 160, 40, Vec2(60.0, 0.5), spacing, mass, Vec2(0.0, 0.0));

  if (next_id != (n1 + n2)) {
    std::cerr << "Erreur de generation des particules\n";
    return EXIT_FAILURE;
  }

  std::ofstream out("tp4_collision.txt");
  out << "# t puis (x y) pour chaque particule\n";

  const int nsteps = static_cast<int>(std::ceil(t_end / dt));
  for (int step = 0; step <= nsteps; ++step) {
    const double t = step * dt;
    if (step % save_every == 0) {
      u.save_state_line(out, t);
    }
    if (step < nsteps) {
      u.step();
    }
  }
  out.close();

  std::cout << "Simulation terminee jusque t=" << t_end << "\n";
  std::cout << "Etat sauvegarde dans tp4_collision.txt\n";
  return EXIT_SUCCESS;
}
