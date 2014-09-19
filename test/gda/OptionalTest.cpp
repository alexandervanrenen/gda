//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2014 Alexander van Renen. All rights reserved.
//
// Purpose - Test optional class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/Optional.hpp"
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(Optional, Number)
{
   Optional<uint32_t> number;
   ASSERT_FALSE(number.isValueSet());
   ASSERT_ANY_THROW((void) (number == 2u));
   number = 2u;
   ASSERT_TRUE(number.isValueSet());

   ASSERT_TRUE(number == 2u);
   ASSERT_TRUE(number != 1u);
   ASSERT_TRUE(number < 3u);
   ASSERT_TRUE(number <= 2u);
   ASSERT_TRUE(number > 1u);
   ASSERT_TRUE(number >= 2u);

   ASSERT_TRUE(number == Optional<uint32_t>(2));
   ASSERT_TRUE(number != Optional<uint32_t>(1));
   ASSERT_TRUE(number < Optional<uint32_t>(3));
   ASSERT_TRUE(number <= Optional<uint32_t>(2));
   ASSERT_TRUE(number > Optional<uint32_t>(1));
   ASSERT_TRUE(number >= Optional<uint32_t>(2));
}
// -------------------------------------------------------------------------------------------------
TEST(Optional, String)
{
   Optional<string> str;
   ASSERT_FALSE(str.isValueSet());
   ASSERT_ANY_THROW((void) (str == "2"));
   str = "2";
   ASSERT_TRUE(str.isValueSet());

   ASSERT_TRUE(str == "2");
   ASSERT_TRUE(str != "1");

   ASSERT_TRUE(str == Optional<string>("2"));
   ASSERT_TRUE(str != Optional<string>("1"));
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
