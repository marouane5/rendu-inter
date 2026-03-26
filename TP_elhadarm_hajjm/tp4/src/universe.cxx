#include "universe.hxx"

#include <algorithm>
#include <cmath>
#include <ostream>

Universe::Universe(double lx, double ly, double cutoff, double epsilon, double sigma, double dt)
    : lx_(lx),
      ly_(ly),
      cutoff_(cutoff),
      cutoff2_(cutoff * cutoff),
      epsilon_(epsilon),
      sigma_(sigma),
      dt_(dt),
      nx_(std::max(1, static_cast<int>(std::floor(lx / cutoff)))),
      ny_(std::max(1, static_cast<int>(std::floor(ly / cutoff)))) {
  cells_.resize(static_cast<std::size_t>(nx_ * ny_));
}

void Universe::add_particle(const Particle &p) {
  Particle copy = p;
  Vec2 pos = copy.position();
  wrap(pos);
  copy.set_position(pos);
  particles_.push_back(copy);
}

std::size_t Universe::particle_count() const {
  return particles_.size();
}

int Universe::nx() const {
  return nx_;
}

int Universe::ny() const {
  return ny_;
}

int Universe::cell_index(int ix, int iy) const {
  return iy * nx_ + ix;
}

void Universe::wrap(Vec2 &p) const {
  p.x = std::fmod(p.x, lx_);
  p.y = std::fmod(p.y, ly_);
  if (p.x < 0.0) {
    p.x += lx_;
  }
  if (p.y < 0.0) {
    p.y += ly_;
  }
}

Vec2 Universe::minimum_image(Vec2 dr) const {
  if (dr.x > 0.5 * lx_) {
    dr.x -= lx_;
  } else if (dr.x < -0.5 * lx_) {
    dr.x += lx_;
  }
  if (dr.y > 0.5 * ly_) {
    dr.y -= ly_;
  } else if (dr.y < -0.5 * ly_) {
    dr.y += ly_;
  }
  return dr;
}

std::pair<int, int> Universe::to_cell(const Vec2 &p) const {
  int ix = static_cast<int>(std::floor(p.x / cutoff_));
  int iy = static_cast<int>(std::floor(p.y / cutoff_));
  if (ix < 0) {
    ix = 0;
  }
  if (iy < 0) {
    iy = 0;
  }
  if (ix >= nx_) {
    ix = nx_ - 1;
  }
  if (iy >= ny_) {
    iy = ny_ - 1;
  }
  return {ix, iy};
}

void Universe::rebuild_cells() {
  for (auto &cell : cells_) {
    cell.clear();
  }

  for (std::size_t i = 0; i < particles_.size(); ++i) {
    Vec2 pos = particles_[i].position();
    wrap(pos);
    particles_[i].set_position(pos);
    const auto [ix, iy] = to_cell(pos);
    cells_[static_cast<std::size_t>(cell_index(ix, iy))].push_back(i);
  }
}

double Universe::lennard_jones_potential(double r) const {
  if (r <= 0.0 || r > cutoff_) {
    return 0.0;
  }
  const double sr = sigma_ / r;
  const double sr6 = std::pow(sr, 6.0);
  const double sr12 = sr6 * sr6;
  return 4.0 * epsilon_ * (sr12 - sr6);
}

void Universe::compute_forces_lj() {
  for (auto &p : particles_) {
    p.reset_force();
  }

  for (int cx = 0; cx < nx_; ++cx) {
    for (int cy = 0; cy < ny_; ++cy) {
      const int c = cell_index(cx, cy);
      const auto &cell_a = cells_[static_cast<std::size_t>(c)];
      if (cell_a.empty()) {
        continue;
      }

      for (int ox = -1; ox <= 1; ++ox) {
        for (int oy = -1; oy <= 1; ++oy) {
          const int nx = (cx + ox + nx_) % nx_;
          const int ny = (cy + oy + ny_) % ny_;
          const int c2 = cell_index(nx, ny);
          if (c2 < c) {
            continue;
          }

          const auto &cell_b = cells_[static_cast<std::size_t>(c2)];
          if (cell_b.empty()) {
            continue;
          }

          for (std::size_t ia = 0; ia < cell_a.size(); ++ia) {
            const std::size_t i = cell_a[ia];
            std::size_t jb_start = 0;
            if (c == c2) {
              jb_start = ia + 1;
            }

            for (std::size_t jb = jb_start; jb < cell_b.size(); ++jb) {
              const std::size_t j = cell_b[jb];
              Vec2 dr = particles_[j].position() - particles_[i].position();
              dr = minimum_image(dr);
              const double r2 = dr.norm2();
              if (r2 < 1e-12 || r2 > cutoff2_) {
                continue;
              }

              const double inv_r2 = 1.0 / r2;
              const double sr2 = (sigma_ * sigma_) * inv_r2;
              const double sr6 = sr2 * sr2 * sr2;
              const double sr12 = sr6 * sr6;
              const double scalar = 24.0 * epsilon_ * (2.0 * sr12 - sr6) * inv_r2;
              const Vec2 fij = scalar * dr;
              particles_[i].add_force(fij);
              particles_[j].add_force(-fij);
            }
          }
        }
      }
    }
  }
}

void Universe::step() {
  rebuild_cells();
  compute_forces_lj();
  for (auto &p : particles_) {
    const Vec2 acc = p.force() / p.mass();
    const Vec2 new_vel = p.velocity() + dt_ * acc;
    Vec2 new_pos = p.position() + dt_ * new_vel;
    wrap(new_pos);
    p.set_velocity(new_vel);
    p.set_position(new_pos);
  }
  rebuild_cells();
}

void Universe::save_state_line(std::ostream &os, double t) const {
  os << t;
  for (const auto &p : particles_) {
    os << " " << p.position().x << " " << p.position().y;
  }
  os << "\n";
}
