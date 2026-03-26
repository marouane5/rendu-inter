#include "trace_utils.hxx"

#include <iostream>
#include <random>
#include <stdexcept>

Matrix initialize_matrix(std::size_t n) {
  return Matrix(n, std::vector<double>(n, 0.0));
}

void fill_matrix(Matrix &matrix, unsigned int seed) {
  std::mt19937 gen(seed);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);
  for (std::size_t i = 0; i < matrix.size(); ++i) {
    for (std::size_t j = 0; j < matrix[i].size(); ++j) {
      matrix[i][j] = dist(gen);
    }
  }
}

void print_matrix(const Matrix &matrix) {
  for (const auto &row : matrix) {
    for (double value : row) {
      std::cout << value << " ";
    }
    std::cout << '\n';
  }
}

double trace_matrix(const Matrix &matrix) {
  if (matrix.empty()) {
    return 0.0;
  }
  if (matrix.size() != matrix[0].size()) {
    throw std::runtime_error("Matrix not square");
  }

  double sum = 0.0;
  for (std::size_t i = 0; i < matrix.size(); ++i) {
    sum += matrix[i][i];
  }
  return sum;
}

std::vector<double> initialize_matrix_flat(std::size_t n) {
  return std::vector<double>(n * n, 0.0);
}

void fill_matrix_flat(std::vector<double> &matrix, std::size_t n, unsigned int seed) {
  std::mt19937 gen(seed);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      matrix[i * n + j] = dist(gen);
    }
  }
}

double trace_matrix_flat(const std::vector<double> &matrix, std::size_t n) {
  if (matrix.size() != n * n) {
    throw std::runtime_error("Bad matrix size");
  }

  double sum = 0.0;
  for (std::size_t i = 0; i < n; ++i) {
    sum += matrix[i * n + i];
  }
  return sum;
}
