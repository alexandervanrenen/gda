#ifndef GDA_TIME_HPP
#define GDA_TIME_HPP
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdint.h>
#include <ostream>
//-----------------------------------------------------------------------------
// Utilities - time
// Alexander van Renen 2011
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
   /// Sets the time to the current time
   void reset();
   /// Sets the time to the difference between the time in the object and now in nano secs
   void setDiff();

   /// The time in the object in Datum format
   const std::string date(uint32_t type = kNorm) const;

   /// converts the time value to a string
   const std::string str() const;

   /// Stores time value in nano seconds
   uint64_t ct;
};
//-----------------------------------------------------------------------------
/// prints the time to the ostream
std::ostream& operator << (std::ostream& os, const Time& t);
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
