#include "string.hpp"
#include <algorithm>
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
   for(unsigned int i=0; i<str.size(); i++)
      if(str[i] == c)
         result++;
   return result;
}
//-----------------------------------------------------------------------------
uint32_t sizeOfLongestLine(const string& str, char c)
{
   uint32_t result = 0;
   uint32_t max = 0;
   for(unsigned int i=0; i<str.size(); i++)
      if(str[i] == c) {
         max = ::max(result, max);
         result = 0;
      } else {
         result++;
      }
   return ::max(result, max);
}
//-----------------------------------------------------------------------------
void filterSpecialChars(string& str)
{
   string tmp = str;
   str = "";
   for(unsigned int i=0; i<tmp.size(); i++)
      if(isalpha(tmp[i]) || isalnum(tmp[i]) || tmp[i] == ' ')
         str += tmp[i];
}
//-----------------------------------------------------------------------------
void split(vector<string>& result, const string& str, char splitter)
{
   string a = str;
   for(unsigned int i = a.find_first_of(splitter); i != string::npos; i = a.find_first_of(splitter)) {
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
   for(unsigned int i = 0; i<str.size(); i++)
      if(str[i] != remove)
         a += str[i];
   str = a;
}
//-----------------------------------------------------------------------------
void removeAllDouble(string& str, char remove)
{
   string result;
   bool last = false;
   for(unsigned int i = 0; i<str.size(); i++) {
      if(str[i] != remove || !last)
         result += str[i];
      last = str[i] == remove;
   }
   str = result;
}
//-----------------------------------------------------------------------------
} // end of namespace convy
//-----------------------------------------------------------------------------
