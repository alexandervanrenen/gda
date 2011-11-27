#include "gtest/gtest.h"
#include "gda/string.hpp"
#include <sstream>
//-----------------------------------------------------------------------------
// Utilities - string processing tests
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
namespace {
//-----------------------------------------------------------------------------
using namespace gda;
using namespace std;
//-----------------------------------------------------------------------------
TEST(string_test, countAppearances) {
   // test basic
   EXPECT_EQ(countAppearances("asd", 'a'), 1u);
   EXPECT_EQ(countAppearances("hello my world", 'l'), 3u);
   EXPECT_EQ(countAppearances("hello my world", 'q'), 0u);
   EXPECT_EQ(countAppearances("", 'a'), 0u);
   
   // random test
   for(uint32_t i=0; i<1000; i++) {
      ostringstream os;
      char refchar = rand();
      uint32_t count = 0;
      for(uint32_t j=0; j<1000; j++) {
         char c = rand();
         if(c==refchar) count++;
         os << c;
         EXPECT_EQ(countAppearances(os.str(), refchar), count);
      }
   }
}
//-----------------------------------------------------------------------------
TEST(string_test, sizeOfLongestLine) {
   // test basic
   EXPECT_EQ(sizeOfLongestLine(""), 0u);
   EXPECT_EQ(sizeOfLongestLine("a"), 1u);
   EXPECT_EQ(sizeOfLongestLine("asd"), 3u);
   EXPECT_EQ(sizeOfLongestLine("asd\nqwe"), 3u);
   EXPECT_EQ(sizeOfLongestLine("asd\n\nqwe"), 3u);
   
   // random test
   
}
//-----------------------------------------------------------------------------
TEST(string_test, filterSpecialChars) {
   EXPECT_EQ(1, 1);
   EXPECT_TRUE(true);
   EXPECT_FALSE(false);
}
//-----------------------------------------------------------------------------
TEST(string_test, split) {
   EXPECT_EQ(1, 1);
   EXPECT_TRUE(true);
   EXPECT_FALSE(false);
}
//-----------------------------------------------------------------------------
TEST(string_test, removeAllDouble) {
   EXPECT_EQ(1, 1);
   EXPECT_TRUE(true);
   EXPECT_FALSE(false);
}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------