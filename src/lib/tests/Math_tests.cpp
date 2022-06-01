#include "TestsHeader.hpp"

TEST_CASE( "Find root of f(x) == 0 by Newtons method", "[NewtonMethod]" )
{
	std::function<double(double)> function = [](double x)->double {
		return x * x - 3 * x + 2;
	};
	double x1 = find_root_newton(function, 1.4);
	double x2 = find_root_newton(function, 1.6);
	
	CHECK(Approx(x1).epsilon(1.e-4) == 1.);
	CHECK(Approx(x2).epsilon(1.e-4) == 2.);
}