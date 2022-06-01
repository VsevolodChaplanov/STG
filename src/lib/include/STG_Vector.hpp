#ifndef __STG_VECTOR__
#define __STG_VECTOR__

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include "STG_Generator.hpp"

namespace STG
{
	// A container containing 3 components of a physical vector
	// {x, y, z} 
	class STGVector
	{
	private:
		// Components of the vector
		std::array<double, 3> __vector;

	public:
		// Default constructor fill vector as: {0, 0, 0}
		STGVector();
		// Fill the vector by a given components
		STGVector(double x, double y, double z);
		~STGVector();
		// Normalize vector to length 1;
		void normalize();
		// Normaize vector to length: lenght
		void normalize_to(double lenght);
		// Generate vector components
		void generate(const STG::IGenerator* generator)
		{
			// При const STG::IGenerator* generator не работает
			// std::generate_n(this->__vector.begin(), 3, generator);
			for (double& elem : __vector)
			{
				elem = generator->operator()();
			}
		}
		// Generate vector components with the same value
		void generate_isotropic(const STG::IGenerator* generator)
		{
			double val = generator->operator()();
			for(double& elem : __vector)
			{
				elem = val;
			}
		}
		// Return a referens to inner array (const)
		const std::array<double, 3>& get_values() const;
		// Set values for given components
		void set_values(double, double, double);
		// Set values for given components
		void set_values(const std::array<double, 3>&);
		// Add a constant value to i-th component
		// 1 = x
		// 2 = y
		// 3 = z
		void add_const_component(double v_av, size_t i);
		// Load of operator [], (const)
		double operator[](size_t i) const;
	}; // class STGVector
} // namespace STG


#endif
