#pragma once

#include "vecteur.hxx"

class Particule {
public:
  Particule() = default;
  Particule(int id, double masse, const Vecteur &position, const Vecteur &vitesse)
      : id_(id), masse_(masse), position_(position), vitesse_(vitesse), force_(0.0, 0.0, 0.0) {}

  int id() const { return id_; }
  double masse() const { return masse_; }
  const Vecteur &position() const { return position_; }
  const Vecteur &vitesse() const { return vitesse_; }
  const Vecteur &force() const { return force_; }

  void set_position(const Vecteur &value) { position_ = value; }
  void set_vitesse(const Vecteur &value) { vitesse_ = value; }

  void reset_force() { force_ = Vecteur(0.0, 0.0, 0.0); }
  void add_force(const Vecteur &value) { force_ += value; }

private:
  int id_ = 0;
  double masse_ = 1.0;
  Vecteur position_;
  Vecteur vitesse_;
  Vecteur force_;
};
