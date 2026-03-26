#pragma once

#include <cstddef>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix initialize_matrix(std::size_t n);
void fill_matrix(Matrix &matrix, unsigned int seed = 42U);
void print_matrix(const Matrix &matrix);
double trace_matrix(const Matrix &matrix);

std::vector<double> initialize_matrix_flat(std::size_t n);
void fill_matrix_flat(std::vector<double> &matrix, std::size_t n, unsigned int seed = 42U);
double trace_matrix_flat(const std::vector<double> &matrix, std::size_t n);
