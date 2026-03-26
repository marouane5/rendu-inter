#pragma once

#include <functional>
#include <vector>

using OdeFunction = std::function<double(double, double)>;

struct OdeResult {
  std::vector<double> t;
  std::vector<double> y;
};

OdeResult explicit_euler(double t0, double t1, int n, double y0, const OdeFunction &f);

OdeResult implicit_euler_fixed_point(
  double t0,
  double t1,
  int n,
  double y0,
  const OdeFunction &f,
  int max_iter = 100,
  double tol = 1e-10
);

OdeResult implicit_euler_linear(
  double t0,
  double t1,
  int n,
  double y0,
  double lambda,
  const std::function<double(double)> &rhs
);
