//
// This file is part of the gda cpp utility library.
// Copyright (c) 2011 Alexander van Renen. All rights reserved.
//
// Purpose - Math utility functions.
// -------------------------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <vector>
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
/// returns next two exponent .. min({ a | a=2^n and a>=num})
uint64_t nextPowerOfTwo(uint64_t num)
{
   num--;
   num |= num >> 1;
   num |= num >> 2;
   num |= num >> 4;
   num |= num >> 8;
   num |= num >> 16;
   num |= num >> 32;
   num++;
   return num;
}
// -------------------------------------------------------------------------------------------------
/// signum function
template<class T>
int32_t signum(T t)
{
   return t > 0 ? 1 : (t < 0 ? -1 : 0);
}
// -------------------------------------------------------------------------------------------------
/// THE CLAMPS !!!
template<class T>
void clamp(std::vector<T>& data, T min, T max)
{
   for (uint32_t i = 0; i < data.size(); i++) {
      if (data[i] < min)
         data[i] = min;
      if (data[i] > max)
         data[i] = max;
   }
}
// -------------------------------------------------------------------------------------------------
/// THE CLAMPS SQUARED !!!
template<class T>
void clamp(std::vector<std::vector<T> >& data, T min, T max)
{
   for (uint32_t i = 0; i < data.size(); i++)
      clamp(data[i], min, max);
}
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
