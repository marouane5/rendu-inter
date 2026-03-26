#pragma once

#include "vec2.hxx"

class Particule {
public:
  Particule() = default;

  Particule(int id, int categorie, double masse, const Vec2 &position, const Vec2 &vitesse)
      : id_(id), categorie_(categorie), masse_(masse), position_(position), vitesse_(vitesse), force_(0.0, 0.0) {}

  int id() const { return id_; }
  int categorie() const { return categorie_; }
  double masse() const { return masse_; }
  const Vec2 &position() const { return position_; }
  const Vec2 &vitesse() const { return vitesse_; }
  const Vec2 &force() const { return force_; }

  void set_position(const Vec2 &value) { position_ = value; }
  void set_vitesse(const Vec2 &value) { vitesse_ = value; }
  void set_masse(double value) { masse_ = value; }
  void set_categorie(int value) { categorie_ = value; }

  void reset_force() { force_ = Vec2(0.0, 0.0); }
  void add_force(const Vec2 &value) { force_ += value; }

  bool operator<(const Particule &other) const { return id_ < other.id_; }

private:
  int id_ = 0;
  int categorie_ = 0;
  double masse_ = 1.0;
  Vec2 position_;
  Vec2 vitesse_;
  Vec2 force_;
};
