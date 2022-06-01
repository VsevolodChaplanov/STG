#include "Math.hpp"
#include <iostream>
#include <functional>

bool compare_vectors(const std::vector<double>& first, const std::vector<double>& second)
{
	if (first.size() != second.size())
	{
		return false;
	}
	for (size_t i = 0; i < first.size(); i++)
	{
		if (first[i] != second[i]) return false;
	}
	return true;	
}

bool compare_vectors(const std::array<double, 3>& first, const std::array<double, 3>& second)
{
	for (size_t i = 0; i < 3; i++)
	{
		if (first[i] != second[i])
		{
			return false;
		}
	}
	return true;
}

void print(const std::vector<double>& vector)
{
	size_t N = vector.size();
	std::cout << typeid(vector).name() << std::endl;
	if (N <= 6)
	{
		for (size_t i = 0; i < N; i++)
		{
			std::cout << i << "\t" << vector[i] << std::endl;
		}
		return;
	}

	for (size_t i = 0; i < 3; i++)
	{
		std::cout << i << "\t" << vector[i] << std::endl;
	}
	std::cout << "..." << std::endl;
	for (size_t i = N - 4; i < N; i++)
	{
		std::cout << i << "\t" << vector[i] << std::endl;
	}	
}

void print(const STG::STGVector& vector)
{
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << i << "\t" << vector[i] << std::endl;
	}
}

void print(const std::array<double ,3>& array)
{
		for (size_t i = 0; i < 3; i++)
	{
		std::cout << i << "\t" << array[i] << std::endl;
	}
}

double find_root_newton(const std::function<double(double)>& function, double x, double dh, double eps, size_t max_it)
{
	int iter = 0;

	double f = 10;

	while(iter < max_it && fabs(f) >= eps)
	{
		f = function(x);
		double df = (function(x+dh) - function(x-dh)) / (2 * dh);
		x = x - f / df;
	}

	return x;
}

// Variation of dot_product function for \vec{k} * \vec{r}
double dot_product(const STG::STGVector& vector, const double* space_point)
{
	double result = vector[0] * space_point[0] + 
		vector[1] * space_point[1] +
		vector[2] * space_point[2];

	return result;
}

