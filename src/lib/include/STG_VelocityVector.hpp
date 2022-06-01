#ifndef __VELOCITY_VECTOR__
#define __VELOCITY_VECTOR__

#include <functional>
#include "STG_Vector.hpp"
#include "Math.hpp"
#include <cmath>

namespace STG
{
	class IVelocity
	{
	protected:

		STG::STGVector velocity;
		const double* space_point;
		double time;
		size_t N = 500; // Dummy number of Fourier modes 
		size_t seed = 1234;

	public:
		IVelocity(const double* point, double time);
		virtual void generate(const STG::IGenerator* engine) = 0;
		const STG::STGVector& get_vector() const;
		void add_const_component(double v_av, size_t i);
		virtual ~IVelocity();
	};	

	class VelocitySmirnov : public IVelocity
	{
	protected:

		double E_spectrum(double k_ampl) const;
		size_t omega_n = 1e3;

	public:
		VelocitySmirnov(const double* point, double time);
		void generate(const STG::IGenerator* engine) override;
		~VelocitySmirnov();
	};

	class VelocityHuang : public IVelocity
	{

	};
} // namespace STG


#endif