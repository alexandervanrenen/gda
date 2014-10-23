//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2014 Alexander van Renen. All rights reserved.
//
// Purpose - Test fast random class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/FastRandom.hpp"
#include <iostream>
#include <cmath>
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(FastRandom, Basic)
{
   const uint32_t kNumValues = 1000000;
   const uint32_t kNumPartitions = 128;
   const uint32_t kNumPerPartition = kNumValues / kNumPartitions;

   vector<uint32_t> nums(kNumPartitions, 0);
   FastRandom ranny;
   for(uint32_t i=0; i< kNumValues; i++)
      nums[ranny.rand() % kNumPartitions]++;

   for(uint32_t i=0; i<128; i++)
      ASSERT_TRUE(kNumPerPartition - kNumPerPartition * .2f < nums[i] && nums[i] < kNumPerPartition + kNumPerPartition * .2f);
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
