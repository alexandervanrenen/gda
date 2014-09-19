//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Test memory ref class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/MemoryRef.hpp"
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(MemoryRef, basics)
{
   vector<char> data{'a', 'b', 'c', 'd', 'e'};
   MemoryRef ref(data.data(), 4);
   ASSERT_EQ(ref.to_string(), "abcd");
   ASSERT_EQ(ref.subRef(0).to_string(), "abcd");
   ASSERT_EQ(ref.subRef(2).to_string(), "cd");
   ASSERT_EQ(ref[2], 'c');
   ASSERT_EQ(ref.size(), 4ul);
   ASSERT_EQ(ref.subRef(2).size(), 2ul);
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
