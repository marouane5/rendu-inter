#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>

class Vecteur {
public:
  Vecteur() : data_{0.0, 0.0, 0.0} {}
  Vecteur(double x, double y, double z) : data_{x, y, z} {}

  double &operator[](std::size_t i) { return data_[i]; }
  double operator[](std::size_t i) const { return data_[i]; }

  Vecteur operator+(const Vecteur &other) const {
    return {data_[0] + other[0], data_[1] + other[1], data_[2] + other[2]};
  }

  Vecteur operator-(const Vecteur &other) const {
    return {data_[0] - other[0], data_[1] - other[1], data_[2] - other[2]};
  }

  Vecteur operator*(double a) const { return {a * data_[0], a * data_[1], a * data_[2]}; }
  Vecteur operator/(double a) const { return {data_[0] / a, data_[1] / a, data_[2] / a}; }

  Vecteur &operator+=(const Vecteur &other) {
    data_[0] += other[0];
    data_[1] += other[1];
    data_[2] += other[2];
    return *this;
  }

  Vecteur &operator-=(const Vecteur &other) {
    data_[0] -= other[0];
    data_[1] -= other[1];
    data_[2] -= other[2];
    return *this;
  }

  Vecteur &operator*=(double a) {
    data_[0] *= a;
    data_[1] *= a;
    data_[2] *= a;
    return *this;
  }

  double norme2() const {
    return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2];
  }

  double norme() const {
    return std::sqrt(norme2());
  }

  static double dot(const Vecteur &a, const Vecteur &b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  }

private:
  std::array<double, 3> data_;
};

inline Vecteur operator*(double a, const Vecteur &v) {
  return v * a;
}

inline std::ostream &operator<<(std::ostream &os, const Vecteur &v) {
  os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
  return os;
}
