#pragma once

#include <cstddef>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix initialize_matrix(std::size_t n);
void fill_matrix(Matrix &matrix, unsigned int seed = 42U);
void print_matrix(const Matrix &matrix);
double trace_matrix(const Matrix &matrix);
