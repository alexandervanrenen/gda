#include "gda/time.hpp"
//-----------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <sys/time.h>
#include <sstream>
//-----------------------------------------------------------------------------
// Utilities - time
// Alexander van Renen 2011
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
Time::Time()
: ct(0)
{
   timeval curTime;
   gettimeofday(&curTime , NULL);
   ct = curTime.tv_sec * 1000000ull + curTime.tv_usec;
}
//-----------------------------------------------------------------------------
Time::Time(uint64_t t)
: ct(t)
{
}
//-----------------------------------------------------------------------------
Time::Time(const Time& t)
: ct(t.ct)
{
}
//-----------------------------------------------------------------------------
const Time& Time::operator= (uint64_t t)
{
   ct = t;
   return *this;
}
//-----------------------------------------------------------------------------
const Time& Time::operator= (const Time& t)
{
   ct = t.ct;
   return *this;
}
//-----------------------------------------------------------------------------
const Time Time::diff() const
{
   Time a;
   return a.ct - ct;
}
//-----------------------------------------------------------------------------
void Time::reset()
{
   timeval curTime;
   gettimeofday(&curTime , NULL);
   ct = curTime.tv_sec * 1000000ull + curTime.tv_usec;
}
//-----------------------------------------------------------------------------
const string Time::date(uint32_t type) const
{
   switch (type) {
      
      case kNorm: {
         time_t currentTime = ct/1000000;
         tm* t = localtime(&currentTime);
         
         ostringstream outStream;
         
         outStream << t->tm_year+1900 << "-"
                   << (t->tm_mon<10?"0":"")  << t->tm_mon  << "-"
                   << (t->tm_mday<10?"0":"") << t->tm_mday << " "
                   << (t->tm_hour<10?"0":"") << t->tm_hour << ":"
                   << (t->tm_min<10?"0":"")  << t->tm_min  << ":"
                   << (t->tm_sec<10?"0":"")  << t->tm_sec;
         return outStream.str();
      }
      default: {
         return "not implemented yet";
      }
   }
}
//-----------------------------------------------------------------------------
const string Time::str() const
{
   static uint64_t pow[8] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
   ostringstream os;
   
   if((ct / 1000000) / 3600 / 24 != 0)
      os << (ct / 1000000) / 24 / 3600 << "d ";
   
   if((ct / 1000000) / 3600 != 0)
      os << (ct / 1000000) / 3600 % 3600 << "h ";
   
   if((ct / 1000000) / 60 != 0)
      os << (ct / 1000000) / 60 % 60 << "m ";
   
   os << (ct / 1000000) % 60 << ".";
   for(int i=5; i>=0; i--)
      os << ct % pow[i+1] / pow[i];
   os << "s";
   return os.str();
}
//-----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const Time& t)
{
   os << t.str();
   return os;
}
//-----------------------------------------------------------------------------
} //end of namespace gda
//-----------------------------------------------------------------------------
