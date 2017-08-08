//
// This file is part of the gda cpp utility library tests.
// Copyright (c) 2017 Alexander van Renen. All rights reserved.
//
// Purpose - A set which stores data inline up to a given size
// -------------------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gda/data_structures/inline_set/InlineSet.hpp"
#include <iostream>
#include <unordered_set>
// -------------------------------------------------------------------------------------------------
namespace {
// -------------------------------------------------------------------------------------------------
using namespace gda;
using namespace std;
// -------------------------------------------------------------------------------------------------
TEST(InlineSet, simple)
{
   gda::InlineSet<uint32_t, 2> test;

   test.insert(28);
   ASSERT_EQ(test.size(), 1u);
   ASSERT_EQ(test.get(0), 28u);

   test.insert(28);
   ASSERT_EQ(test.size(), 1u);
   ASSERT_EQ(test.get(0), 28u);

   test.insert(8128);
   ASSERT_EQ(test.size(), 2u);
   ASSERT_EQ(test.get(0), 28u);
   ASSERT_EQ(test.get(1), 8128u);

   test.insert(6);
   ASSERT_EQ(test.size(), 3u);
   ASSERT_EQ(test.get(0), 6u);
   ASSERT_EQ(test.get(1), 28u);
   ASSERT_EQ(test.get(2), 8128u);

   test.erase(3);
   ASSERT_EQ(test.size(), 3u);
   ASSERT_EQ(test.get(0), 6u);
   ASSERT_EQ(test.get(1), 28u);
   ASSERT_EQ(test.get(2), 8128u);

   test.erase(28);
   ASSERT_EQ(test.size(), 2u);
   ASSERT_EQ(test.get(0), 6u);
   ASSERT_EQ(test.get(1), 8128u);

   test.erase(8128);
   ASSERT_EQ(test.size(), 1u);
   ASSERT_EQ(test.get(0), 6u);

   test.erase(6);
   ASSERT_EQ(test.size(), 0u);
}
// -------------------------------------------------------------------------------------------------
TEST(InlineSet, random)
{
   for (uint32_t run = 0; run<1000; run++) {
      gda::InlineSet<uint32_t, 16> test;
      unordered_set<uint32_t> reference;

      for (uint32_t op = 0; op<2000; op++) {
         switch (rand() % 2) {
            case 0: { // Insert
               uint32_t val = rand() % 100;
               test.insert(val);
               reference.insert(val);
               ASSERT_TRUE(test.contains(val));
               break;
            }
            case 1: { // Remove
               uint32_t val = rand() % 100;
               if (reference.count(val) == 1) {
                  ASSERT_TRUE(test.contains(val));
               } else {
                  ASSERT_FALSE(test.contains(val));
               }

               reference.erase(val);
               test.erase(val);
               ASSERT_FALSE(test.contains(val));
               break;
            }
            default:
               throw;
         }
         ASSERT_EQ(reference.size(), test.size());
      }

      for (uint32_t i = 0; i<test.size(); i++) {
         ASSERT_EQ(1u, reference.count(test.get(i)));
         reference.erase(test.get(i));
      }
   }
}
// -------------------------------------------------------------------------------------------------
} // End of anonymous namespace
// -------------------------------------------------------------------------------------------------
