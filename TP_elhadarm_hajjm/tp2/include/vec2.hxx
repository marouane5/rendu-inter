#pragma once

#include <cmath>

struct Vec2 {
  double x = 0.0;
  double y = 0.0;

  Vec2() = default;
  Vec2(double x_, double y_) : x(x_), y(y_) {}

  Vec2 operator+(const Vec2 &other) const { return {x + other.x, y + other.y}; }
  Vec2 operator-(const Vec2 &other) const { return {x - other.x, y - other.y}; }
  Vec2 operator-() const { return {-x, -y}; }
  Vec2 operator*(double a) const { return {x * a, y * a}; }
  Vec2 operator/(double a) const { return {x / a, y / a}; }

  Vec2 &operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 &operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  double norm() const { return std::sqrt(x * x + y * y); }
  double norm2() const { return x * x + y * y; }
};

inline Vec2 operator*(double a, const Vec2 &v) {
  return {a * v.x, a * v.y};
}
