#pragma once

#include "vec2.hxx"

class Particle {
public:
  Particle() = default;
  Particle(int id, int type, double mass, const Vec2 &position, const Vec2 &velocity)
      : id_(id), type_(type), mass_(mass), position_(position), velocity_(velocity), force_(0.0, 0.0) {}

  int id() const { return id_; }
  int type() const { return type_; }
  double mass() const { return mass_; }
  const Vec2 &position() const { return position_; }
  const Vec2 &velocity() const { return velocity_; }
  const Vec2 &force() const { return force_; }

  void set_position(const Vec2 &v) { position_ = v; }
  void set_velocity(const Vec2 &v) { velocity_ = v; }
  void reset_force() { force_ = Vec2(0.0, 0.0); }
  void add_force(const Vec2 &v) { force_ += v; }

private:
  int id_ = 0;
  int type_ = 0;
  double mass_ = 1.0;
  Vec2 position_;
  Vec2 velocity_;
  Vec2 force_;
};
