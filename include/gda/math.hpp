#ifndef GDA_MATH_HPP
#define GDA_MATH_HPP
//-----------------------------------------------------------------------------
#include <stdint.h>
//-----------------------------------------------------------------------------
// Utilities - string processing
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
/// returns next two exponent .. min({ a | a=2^n and a>=num})
uint64_t nextPowerOfTwo(uint64_t num);
/// signum function
template<class T>
int32_t signum(T t)
{
   return t>0?1:(t<0?-1:0);
}
}
//-----------------------------------------------------------------------------
#endif
