#include <STG_VelocityVector.hpp>

STG::IVelocity::IVelocity(const double* point, double time) : space_point(point), time(time) { }

const STG::STGVector& STG::IVelocity::get_vector() const
{
	return this->velocity;
}

void STG::IVelocity::add_const_component(double v_av, size_t i)
{
	velocity.add_const_component(v_av, i);
}


STG::IVelocity::~IVelocity()
{
	// delete space_point;
}

STG::VelocitySmirnov::VelocitySmirnov(const double* point, double time) : STG::IVelocity(point, time) { }

STG::VelocitySmirnov::~VelocitySmirnov() { }

void STG::VelocitySmirnov::generate(const STG::IGenerator* engine)
{
	STG::STGVector q;
	STG::STGVector p;
	STG::STGVector k;

	double k_ampl_min = 0.5;
	double k_ampl_max = 2;
	double dk = (k_ampl_max - k_ampl_min) / (N - 1);

	double vx = 0;
	double vy = 0;
	double vz = 0;

	for (size_t i = 0; i < N; i++)
	{
		q.generate(engine);
		p.generate(engine);
		k.generate_isotropic(engine);
		k.normalize_to(k_ampl_min + i * dk); // E_spectrum(k_ampl_min + dk)

		vx += (p[0] * cos(dot_product(k, space_point) + i * omega_n * time) + q[0] * sin(dot_product(k, space_point) + i * omega_n * time));
		vy += (p[1] * cos(dot_product(k, space_point) + i * omega_n * time) + q[1] * sin(dot_product(k, space_point) + i * omega_n * time));
		vz += (p[2] * cos(dot_product(k, space_point) + i * omega_n * time) + q[2] * sin(dot_product(k, space_point) + i * omega_n * time));
	}
	this->velocity = {vx * sqrt(2. / (double)N), vy * sqrt(2. / (double)N), vz * sqrt(2. / (double)N)};
}

double STG::VelocitySmirnov::E_spectrum(double k_ampl) const
{
	// 16 (2/pi)^(1/2) k^4 e^(-2 k^2)
	return 16*sqrt(2 / M_PI) * k_ampl * k_ampl * k_ampl * k_ampl * exp(-2 * k_ampl * k_ampl);
}