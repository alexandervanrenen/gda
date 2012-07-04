#ifndef GDA_MATH_HPP
#define GDA_MATH_HPP
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <vector>
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
/// THE CLAMPS !!!
template<class T>
void clamp(std::vector<T>& data, T min, T max)
{
   for(uint32_t i=0; i<data.size(); i++) {
      if(data[i]<min)
         data[i]=min;
      if(data[i]>max)
         data[i]=max;
   }
}
/// THE CLAMPS SQUARED !!!
template<class T>
void clamp(std::vector<std::vector<T> >& data, T min, T max)
{
   for(uint32_t i=0; i<data.size(); i++)
      clamp(data[i], min, max);
}
}
//-----------------------------------------------------------------------------
#endif
