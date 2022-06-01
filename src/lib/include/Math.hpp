#ifndef __VECTOR_MATH__
#define __VECTOR_MATH__

#include <vector>
#include <array>
#include <cmath>
#include <functional>
#include "STG_VelocityVector.hpp"

bool compare_vectors(const std::vector<double>& first, const std::vector<double>& second);
bool compare_vectors(const std::array<double, 3>& first, const std::array<double, 3>& second);
void print(const std::vector<double>& vector);
void print(const std::array<double ,3>& array);
void print(const STG::STGVector& vector);
double find_root_newton(const std::function<double(double)>& function, double x, double dh = 1.e-2, double eps = 1.e-5, size_t max_it = 2000);
double dot_product(const STG::STGVector& vector, const double* space_point);

#endif
