#include "gda/string.hpp"
#include <algorithm>
#include <iostream>
//-----------------------------------------------------------------------------
// Utilities - string processing
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
uint32_t countAppearances(const string& str, char c)
{
   uint32_t result = 0;
   for(uint32_t i=0; i<str.size(); i++)
      if(str[i] == c)
         result++;
   return result;
}
//-----------------------------------------------------------------------------
uint32_t sizeOfLongestLine(const string& str, char c)
{
   uint32_t result = 0;
   uint32_t max = 0;
   for(uint32_t i=0; i<str.size(); i++)
      if(str[i] == c) {
         max = ::max(result, max);
         result = 0;
      } else {
         result++;
      }
   return ::max(result, max);
}
//-----------------------------------------------------------------------------
string filterSpecialChars(const string& str)
{
   ostringstream result("");
   for(uint32_t i=0; i<str.size(); i++)
      if(isalpha(str[i]) || isalnum(str[i]) || str[i] == ' ')
         result << str[i];
   return result.str();
}
//-----------------------------------------------------------------------------
void split(vector<string>& result, const string& str, char splitter)
{
   string a = str;
   for(size_t i=a.find_first_of(splitter); i!=string::npos; i=a.find_first_of(splitter)) {
      if(a.find_first_of(splitter) == string::npos)
         throw;
      result.push_back(a.substr(0, i));
      a = a.substr(i+1, a.size());
   }
   if(a.size() != 0)
      result.push_back(a.substr(0, a.size()));
}
//-----------------------------------------------------------------------------
void removeAll(string& str, char remove)
{
   string a;
   for(uint32_t i = 0; i<str.size(); i++)
      if(str[i] != remove)
         a += str[i];
   str = a;
}
//-----------------------------------------------------------------------------
string removeAllDouble(const string& str, char remove)
{
   string result;
   bool last = false;
   for(uint32_t i = 0; i<str.size(); i++) {
      if(str[i] != remove || !last)
         result += str[i];
      last = str[i] == remove;
   }
   return result;
}
//-----------------------------------------------------------------------------
string randomString(uint32_t len)
{
   string charsToUse;
   for(uint32_t i=0; i<256; i++)
      charsToUse += static_cast<char>(i);
   return randomString(len, charsToUse);
}
//-----------------------------------------------------------------------------
string randomAlphaString(uint32_t len)
{
   string charsToUse = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   return randomString(len, charsToUse);
}
//-----------------------------------------------------------------------------
string randomNumbericString(uint32_t len)
{
   string charsToUse = "0123456789";
   return randomString(len, charsToUse);
}
//-----------------------------------------------------------------------------
string randomAlphaNumericString(uint32_t len)
{
   string charsToUse = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   return randomString(len, charsToUse);
}
//-----------------------------------------------------------------------------
string randomString(uint32_t len, const string& charsToUse)
{
   ostringstream os("");
   for(uint32_t i=0; i<len; i++)
      os << charsToUse[rand()%charsToUse.size()];
   return os.str();
}
//-----------------------------------------------------------------------------
} // end of namespace convy
//-----------------------------------------------------------------------------
