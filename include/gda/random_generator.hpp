#ifndef GDA_RANDOM_GENERATOR_HPP
#define GDA_RANDOM_GENERATOR_HPP
//-----------------------------------------------------------------------------
#include <stdint.h>
//-----------------------------------------------------------------------------
// Utilities - random number generator
// Alexander van Renen 2012 (the algo itselfe is not mine ..)
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
class RandomGenerator {
public:
   RandomGenerator(uint64_t seed = 88172645463325252ull);
   uint64_t rand();
   float randScaleFactor(); // returns float between 0 and 1
   uint64_t seed;
};
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
#endif
