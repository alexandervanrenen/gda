#ifndef _HELPER_H
#define _HELPER_H
//-----------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <vector>
//-----------------------------------------------------------------------------
// Utilities - string processing
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
/// number --> string
template<class Number>
string toString(const Number num)
{
   ostringstream stream;
   stream << num;
   return stream.str();
}
//-----------------------------------------------------------------------------
/// string --> number
template<class Number>
Number toNumber(const string& str)
{
   Number num;
   istringstream stream(str);
   stream >> num;
   return num;
}
//-----------------------------------------------------------------------------
/// clears the string, afterwards it will just contain: ([a-z][A-Z][0-9])*
void filterSpecialChars(string& str);
//-----------------------------------------------------------------------------
/// splits the string at the splitter parameter and stores the pices in result
void split(vector<string>& result, const string& str, char splitter);
//-----------------------------------------------------------------------------
/// the specified character is limited to only one apereance in a row
void removeAllDouble(string& str, char remove);
}
//-----------------------------------------------------------------------------
#endif
