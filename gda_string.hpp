#ifndef GDA_STRING_HPP
#define GDA_STRING_HPP
//-----------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <stdint.h>
#include <vector>
//-----------------------------------------------------------------------------
// Utilities - string processing
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
/// counts number of appearances of c in string str
uint32_t countAppearances(const string& str, char c);
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
