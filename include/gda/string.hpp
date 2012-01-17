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
namespace gda {
/// counts number of appearances of c in std::string str
uint32_t countAppearances(const std::string& str, char c);

/// calculates the size of the longest line
uint32_t sizeOfLongestLine(const std::string& str, char c = '\n');

/// clears the std::string, afterwards it will just contain: ([a-z][A-Z][0-9])*
std::string filterSpecialChars(const std::string& str);

/// splits the std::string at the splitter parameter and stores the pices in result
void split(std::vector<std::string>& result, const std::string& str, char splitter);

/// the specified character is limited to only one apereance in a row
std::string removeAllDouble(const std::string& str, char remove);

/// returns the remaining content of the stream in form of a string
std::string getRemainingContent(std::istream& in);

/// produces a random string
std::string randomString(uint32_t len);
std::string randomAlphaString(uint32_t len);
std::string randomNumbericString(uint32_t len);
std::string randomAlphaNumericString(uint32_t len);
std::string randomString(uint32_t len, const std::string& charsToUse);

/// the exception which gets thrown when parsing a number fails
struct NoNumber {};

/// number --> string
template<class Number>
std::string to_string(const Number& num, bool useThrowOnError=false)
{
   std::ostringstream stream;
   stream << num;
   if(useThrowOnError && !stream.good())
      throw NoNumber();
   return stream.str();
}

/// string --> number
template<class Number>
Number to_number(const std::string& str, bool useThrowOnError=false)
{
   Number num;
   std::istringstream stream(str);
   stream >> num;
   if(useThrowOnError && !stream.good())
      throw NoNumber();
   return num;
}
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
