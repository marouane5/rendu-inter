#include "ode.hxx"

#include <cmath>
#include <stdexcept>

namespace {

double step_size(double t0, double t1, int n) {
  if (n <= 0) {
    throw std::runtime_error("n must be > 0");
  }
  return (t1 - t0) / static_cast<double>(n);
}

} // namespace

OdeResult explicit_euler(double t0, double t1, int n, double y0, const OdeFunction &f) {
  const double h = step_size(t0, t1, n);
  OdeResult result;
  result.t.resize(static_cast<std::size_t>(n) + 1U);
  result.y.resize(static_cast<std::size_t>(n) + 1U);
  result.t[0] = t0;
  result.y[0] = y0;

  for (int i = 0; i < n; ++i) {
    const std::size_t k = static_cast<std::size_t>(i);
    result.t[k + 1U] = result.t[k] + h;
    result.y[k + 1U] = result.y[k] + h * f(result.t[k], result.y[k]);
  }

  return result;
}

OdeResult implicit_euler_fixed_point(
  double t0,
  double t1,
  int n,
  double y0,
  const OdeFunction &f,
  int max_iter,
  double tol
) {
  const double h = step_size(t0, t1, n);
  OdeResult result;
  result.t.resize(static_cast<std::size_t>(n) + 1U);
  result.y.resize(static_cast<std::size_t>(n) + 1U);
  result.t[0] = t0;
  result.y[0] = y0;

  for (int i = 0; i < n; ++i) {
    const std::size_t k = static_cast<std::size_t>(i);
    const double t_next = result.t[k] + h;
    double y_next = result.y[k];

    for (int iter = 0; iter < max_iter; ++iter) {
      const double candidate = result.y[k] + h * f(t_next, y_next);
      if (std::abs(candidate - y_next) < tol) {
        y_next = candidate;
        break;
      }
      y_next = candidate;
    }

    result.t[k + 1U] = t_next;
    result.y[k + 1U] = y_next;
  }

  return result;
}

OdeResult implicit_euler_linear(
  double t0,
  double t1,
  int n,
  double y0,
  double lambda,
  const std::function<double(double)> &rhs
) {
  const double h = step_size(t0, t1, n);
  OdeResult result;
  result.t.resize(static_cast<std::size_t>(n) + 1U);
  result.y.resize(static_cast<std::size_t>(n) + 1U);
  result.t[0] = t0;
  result.y[0] = y0;

  const double denom = 1.0 - h * lambda;
  if (std::abs(denom) < 1e-14) {
    throw std::runtime_error("Invalid denominator in implicit linear Euler");
  }

  for (int i = 0; i < n; ++i) {
    const std::size_t k = static_cast<std::size_t>(i);
    const double t_next = result.t[k] + h;
    const double b_next = rhs(t_next);
    result.t[k + 1U] = t_next;
    result.y[k + 1U] = (result.y[k] + h * b_next) / denom;
  }

  return result;
}
