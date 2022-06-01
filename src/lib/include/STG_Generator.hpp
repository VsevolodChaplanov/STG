#ifndef __STG_GENERATORS_INTERFACE__
#define __STG_GENERATORS_INTERFACE__

#include <functional>

namespace STG
{
	// --------------------------------------------------------
	//					GeneratorEngine
	//		|					|					|
	// 	MersenTwister 	LinearCongruental	SubsctractWithCarry
	// --------------------------------------------------------

	// --------------------------------------------------------
	//					DistributionEngine
	//		|					|					|
	//	Normal				Uniform				Poisson
	// --------------------------------------------------------

	// --------------------------------------------------------
	// Генератор GeneratorEngine -> DistributionEngine
	// --------------------------------------------------------

	// --------------------------------------------------------
	// 						Normal
	//		|			|		|
	//	 Caushy		Gauss	Fisher		...
	// --------------------------------------------------------

	// --------------------------------------------------------
	//						Uniform
	//				|					|
	//			Uniform Int			Uniform Real
	// --------------------------------------------------------

	class IGenerator
	{
	public:
		// IGenerator();
		virtual double operator()() const = 0;
		// template<class G, class D>
		// static IGenerator* create_Engine(double param_1, double param_2, size_t seed)
		// {
		// 	return new Generator<G, D>(param_1, param_2, seed);
		// }
		virtual ~IGenerator() { }
	};

	// G == Generator engine
	// D == Distribution
	template<class G, class D>
	class Generator : public IGenerator
	{
	private:
		std::function<double()> generating_function;
		G gen_engine;
		D dist_engine;
	public:

		Generator(double param_1, double param_2, size_t seed)
		{
			G engine(seed);
			D dist(param_1, param_2);
			this->gen_engine = engine;
			this->dist_engine = dist;
			this->generating_function = [this]()->double{
				return dist_engine(gen_engine);
			};
		}
		double operator()() const override
		{
			return this->generating_function();
		}
		~Generator() { }
	};
} // namespace STG

#endif