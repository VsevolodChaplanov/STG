#include "STG_Vector.hpp"

STG::STGVector::STGVector() 
{
	this->__vector = {0, 0, 0};
}

STG::STGVector::STGVector(double x, double y, double z) 
{
	this->__vector = {x, y, z};
}

void STG::STGVector::normalize()
{
	double length = __vector[0] * __vector[0] + __vector[1] * __vector[1] + __vector[2] * __vector[2];
	__vector[0] = __vector[0] / length;
	__vector[1] = __vector[1] / length;
	__vector[2] = __vector[2] / length;
}

void STG::STGVector::normalize_to(double length)
{
	double vec_length = __vector[0] * __vector[0] + __vector[1] * __vector[1] + __vector[2] * __vector[2];
	__vector[0] = __vector[0] / vec_length * length;
	__vector[1] = __vector[1] / vec_length * length;
	__vector[2] = __vector[2] / vec_length * length;
}

const std::array<double, 3>& STG::STGVector::get_values() const
{
	return this->__vector;
}

void STG::STGVector::set_values(double x, double y, double z)
{
	this->__vector[0] = x;
	this->__vector[1] = y;
	this->__vector[2] = z;
}

void STG::STGVector::set_values(const std::array<double, 3>& vector)
{
	this->__vector = vector;
}

double STG::STGVector::operator[](size_t i) const
{
	if (i > 2)
	{
		throw std::range_error("Index i is out of range (>2)");
	}
	return this->__vector[i];
}

void STG::STGVector::add_const_component(double v_av, size_t i)
{
	if (i > 2)
	{
		throw std::invalid_argument("Index is out of range");
	}
	__vector[i] += v_av;
}

STG::STGVector::~STGVector() { }
