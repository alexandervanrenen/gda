//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Test color class.
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/Color.hpp"
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(ColorTest, basics)
{
   ColorRGB color(Color::Red);
   ASSERT_EQ(color.str(), "255 0 0");
   ASSERT_EQ(color.integer(), 0xFF0000ul);

   color.change(Color::Blue);
   ASSERT_EQ(color.str(), "0 0 255");
   ASSERT_EQ(color.integer(), 0x0000FFul);

   color.change("031506");
   ASSERT_EQ(color.str(), "3 21 6");
   ASSERT_EQ(color.integer(), 0x031506ul);

   color.change(ColorHelper::stringToType("Green"));
   ASSERT_EQ(color.str(), "0 255 0");
   ASSERT_EQ(color.integer(), 0x00FF00ul);

   color.change(0x23u, 0x8Au, 0xABu);
   ASSERT_EQ(color.str(), "35 138 171");
   ASSERT_EQ(color.integer(), 0x238AABul);
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
