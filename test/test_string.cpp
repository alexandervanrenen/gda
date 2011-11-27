#include "gtest/gtest.h"
#include "gda/string.hpp"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
// Utilities - string processing tests
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
namespace {
//-----------------------------------------------------------------------------
using namespace gda;
using namespace std;
//-----------------------------------------------------------------------------
TEST(string_test, countAppearances)
{
   // test basic
   EXPECT_EQ(countAppearances("asd", 'a'), 1u);
   EXPECT_EQ(countAppearances("hello my world", 'l'), 3u);
   EXPECT_EQ(countAppearances("hello my world", 'q'), 0u);
   EXPECT_EQ(countAppearances("", 'a'), 0u);

   // random test
   for(uint32_t i=0; i<1000; i++) {
      ostringstream os("");
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
TEST(string_test, sizeOfLongestLine)
{
   // test basic
   EXPECT_EQ(sizeOfLongestLine(""), 0u);
   EXPECT_EQ(sizeOfLongestLine("a"), 1u);
   EXPECT_EQ(sizeOfLongestLine("asd"), 3u);
   EXPECT_EQ(sizeOfLongestLine("asd\nqwe"), 3u);
   EXPECT_EQ(sizeOfLongestLine("asd\n\nqwe"), 3u);

   // random test
   for(uint32_t i=0; i<1000; i++) {
      ostringstream os("");
      char refchar = rand();
      uint32_t max = 0;
      for(uint32_t i=0; i<50; i++) {
         uint32_t count = 0;
         char c;
         for(c=rand(); c != refchar; c=rand(), count++)
            os << c;
         os << c;
         max = ::max(count, max);
         count = 0;
         EXPECT_EQ(sizeOfLongestLine(os.str(), refchar), max);
      }
   }
}
//-----------------------------------------------------------------------------
TEST(string_test, filterSpecialChars)
{
   // test basic
   EXPECT_STREQ(filterSpecialChars("").c_str(), "");
   EXPECT_STREQ(filterSpecialChars("asd").c_str(), "asd");
   EXPECT_STREQ(filterSpecialChars("hello my world!").c_str(), "hello my world");
   EXPECT_STREQ(filterSpecialChars("1234567890").c_str(), "1234567890");
   EXPECT_STREQ(filterSpecialChars("abcdefghijklmnopqrstuvwxyz").c_str(), "abcdefghijklmnopqrstuvwxyz");
   EXPECT_STREQ(filterSpecialChars("ABCDEFGHIJKLMNOPQRSTUVWXYZ").c_str(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   EXPECT_STREQ(filterSpecialChars("!\"§$%&/()=???\\+*~#'<>|-_.:;,").c_str(), "");
}
//-----------------------------------------------------------------------------
TEST(string_test, split)
{
   //test basic
   {
      vector<string> vec;
      split(vec, "", ' ');
      EXPECT_EQ(vec.size(), 0u);
   }

   // random test
   for(uint32_t i=0; i<10000; i++) {
      char refchar = rand();
      uint32_t numWords = rand()%40;
      ostringstream validChars("");
      for(uint32_t j=0; j<256; j++)
         if(static_cast<char>(j) != refchar)
            validChars << static_cast<char>(j);
      vector<string> vec;
      string text;
      
      for(uint32_t j=0; j<numWords; j++) {
         const string& str = randomString(rand()%100, validChars.str());
         vec.push_back(str);
         text += str;
         text += refchar;
      }
      
      vector<string> result;
      split(result, text, refchar);
      
      for(uint32_t j=0; j<numWords; j++)
         EXPECT_STREQ(result[j].c_str(), vec[j].c_str());
   }
}
//-----------------------------------------------------------------------------
TEST(string_test, removeAllDouble)
{
   // test basic
   EXPECT_STREQ(removeAllDouble("", 'a').c_str(), "");
   EXPECT_STREQ(removeAllDouble("asd", 'a').c_str(), "asd");
   EXPECT_STREQ(removeAllDouble("aassdd", 'a').c_str(), "assdd");

   // random test
   for(uint32_t i=0; i<10000; i++) {
      char testChar = rand();
      string str1 = randomString(rand()%20);
      bool valid = true;
      for(uint32_t j=1; j<str1.size(); j++) {
         if(str1[j] == str1[j-1] && str1[j] == testChar) {
            valid = false;
            break;
         }
      }
      string str2 = randomString(rand()%20);
      for(uint32_t j=1; j<str2.size(); j++) {
         if(str2[j] == str2[j-1] && str2[j] == testChar) {
            valid = false;
            break;
         }
      }
      valid &= str1[str1.size()-1]!=testChar && str2[0]!=testChar;
      if(!valid)
         continue;
      
      ostringstream osTestInput("");
      osTestInput << str1 << testChar << testChar << str2;
      ostringstream osTestOutput("");
      osTestOutput << str1 << testChar << str2;
      EXPECT_STREQ(removeAllDouble(osTestInput.str(), testChar).c_str(), osTestOutput.str().c_str());
   }
}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------