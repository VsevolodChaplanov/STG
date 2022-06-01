#include "TestsHeader.hpp"

// Test-cases 
// Generator engines
//		Mersen-Twister
//			Normal
// 		Linear Congruential
//			Normal
//		Subtract With Carry
//			Normal


// typedef mt19937 default_random_engine;
// typedef shuffle_order_engine<minstd_rand0, 256> knuth_b;
// typedef linear_congruential_engine<unsigned int, 16807, 0, 2147483647> minstd_rand0;
// typedef linear_congruential_engine<unsigned int, 48271, 0, 2147483647> minstd_rand;
// typedef mersenne_twister_engine<
//     unsigned int, 32, 624, 397,
//     31, 0x9908b0df,
//     11, 0xffffffff,
//     7, 0x9d2c5680,
//     15, 0xefc60000,
//     18, 1812433253> mt19937;
// typedef mersenne_twister_engine<
//     unsigned long long, 64, 312, 156,
//     31, 0xb5026f5aa96619e9ULL,
//     29, 0x5555555555555555ULL,
//     17, 0x71d67fffeda60000ULL,
//     37, 0xfff7eee000000000ULL,
//     43, 6364136223846793005ULL> mt19937_64;
// typedef discard_block_engine<ranlux24_base, 223, 23> ranlux24;
// typedef subtract_with_carry_engine<unsigned int, 24, 10, 24> ranlux24_base;
// typedef discard_block_engine<ranlux48_base, 389, 11> ranlux48;
// typedef subtract_with_carry_engine<unsigned long long, 48, 5, 12> ranlux48_base;

TEST_CASE("Generate Mersen-Twister Normal vector", "[MersenTwister][Engines][NormalDist]" )
{
	size_t seed = 2134;
	STG::Generator<std::mt19937, std::normal_distribution<>> genengine(0, 1, seed);

	STG::STGVector test_vector;
	test_vector.generate(&genengine);
	
	CHECK(
		compare_vectors(test_vector.get_values(), {1.77266518002985147, 0.9075056530555774, -1.8209919634998468})
	);
	// print(test_vector.get_values());
}

TEST_CASE("Generate Linear Congruential Normal vector", "[Minstd][Engines][NormalDist]" )
{
	size_t seed = 2134;
	STG::Generator<std::minstd_rand, std::normal_distribution<>> genengine(0, 1, seed);

	STG::STGVector test_vector;
	test_vector.generate(&genengine);

	CHECK(
		compare_vectors(test_vector.get_values(), {1.8620356667293056, -0.38235666827807185, -0.57227603812841221})
	);
	// print(test_vector.get_values());
}

TEST_CASE("Generate Subtract With Carry Normal vector", "[RanLux48][Engines][NormalDist]" )
{
	size_t seed = 2134;
	STG::Generator<std::ranlux48, std::normal_distribution<>> genengine(0, 1, seed);

	STG::STGVector test_vector;
	test_vector.generate(&genengine);


	CHECK(
		compare_vectors(test_vector.get_values(), {1.2824308987789692, 0.78451574513432676, -0.5786826610395247})
	);
	// print(test_vector.get_values());
}