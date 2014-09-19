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
// Credit to Warens Hacker's Delight
inline uint32_t nextPowerOfTwo(uint32_t n)
{
   n--;
   n |= n >> 1;
   n |= n >> 2;
   n |= n >> 4;
   n |= n >> 8;
   n |= n >> 16;
   return ++n;
}
// -------------------------------------------------------------------------------------------------
// Credit to http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
// Read only code: just worship the gods that revealed it to mankind and don't attempt to understand it ;)
inline uint32_t countSetBits(uint32_t n)
{
   n = n - ((n >> 1) & 0x55555555);
   n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
   return (((n + (n >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
