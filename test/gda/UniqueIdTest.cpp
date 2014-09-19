//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2013 Alexander van Renen. All rights reserved.
//
// Purpose - Test unique id providers.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/UniqueId.hpp"
#include <set>
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(UniqueIdTest, Timestamps)
{
   set<uint64_t> seen;
   UniqueTimestamp ts;
   for (uint32_t i = 0; i < 10000; i++) {
      uint64_t next = ts.getNext();
      ASSERT_EQ(seen.count(next), 0ull);
      seen.insert(next);
   }
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
