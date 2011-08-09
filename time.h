#ifndef _TIME_HPP
#define _TIME_HPP
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdint.h>
//-----------------------------------------------------------------------------
// Utilities - time
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
/// Constants for date function, changes the output format
const static uint32_t kNorm = 0;
const static uint32_t kDate = 1;
const static uint32_t kTime = 2;
const static uint32_t kType = 3;
//-----------------------------------------------------------------------------
/// Contains some functions for easy time handling
class Time {
   public:
   /// Constructors
   Time();
   Time(uint64_t time);
   Time(const Time& t);
   const Time& operator= (uint64_t time);
   const Time& operator= (const Time& t);
   
   /// Get difference between the time in the object and now in nano secs
   const Time diff() const;
   
   /// The time in the object in Datum format
   const string date(uint32_t type = kNorm) const;
   
   /// Sets the time to the current time
   void reset();
   
   /// To string convertion
   operator const char*() const;
   operator const string() const;
   const string str() const;
   
   /// Stores time value in nano seconds
   uint64_t ct;
};
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
