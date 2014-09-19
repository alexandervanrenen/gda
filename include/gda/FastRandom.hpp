//
// This file is part of the gda cpp utility library.
// Copyright (c) 2014 Alexander van Renen. All rights reserved.
//
// Purpose - Creates random numbers.
// Contributions - Thomas Neumann
// -------------------------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------------------------
#include <stdint.h>
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
class FastRandom {
public:
   FastRandom(uint64_t seed = 88172645463325252ull);
   uint64_t rand();
   float randScaleFactor(); // returns float between 0 and 1
   uint64_t seed;
};
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
