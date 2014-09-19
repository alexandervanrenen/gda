//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Test conversion class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/Conversion.hpp"
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(Conversion, Good)
{
   ASSERT_EQ("1337", to_string(1337ul));

   ASSERT_EQ(to_number_no_throw<uint32_t>("1337"), 1337ul);
   ASSERT_EQ(to_number<uint32_t>("1337"), 1337ul);

   for(uint32_t i=0; i<10000; i++) {
      int32_t r = rand();
      ASSERT_EQ(r, to_number_no_throw<int32_t>(to_string(r)));
      ASSERT_EQ(r, to_number<int32_t>(to_string(r)));
   }
}
// -------------------------------------------------------------------------------------------------
TEST(Conversion, Bad)
{
   ASSERT_THROW(to_number<uint32_t>("a"), NoNumber);
}
// -------------------------------------------------------------------------------------------------
TEST(Conversion, Failing)
{
   ASSERT_THROW(to_number<uint32_t>("-1"), NoNumber);
   ASSERT_THROW(to_number<uint32_t>("10000000000"), NoNumber);
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
