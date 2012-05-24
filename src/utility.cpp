#include "gda/utility.hpp"
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <limits>
//-----------------------------------------------------------------------------
// Utilities - general helper funtions
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
bool hasNewEvents(uint32_t fileDescriptor, int64_t waitTime)
{
   //set time
   timeval tv;
   if(waitTime/1000 > numeric_limits<int32_t>::max())
      throw "specified time is too large";
   tv.tv_sec = waitTime/1000;
   tv.tv_usec = (waitTime%1000)*1000;

   //add the socket of this client to the set on which select will listen
   fd_set rfds;
   FD_ZERO(&rfds);
   FD_SET(fileDescriptor, &rfds);
   int retval = select(fileDescriptor+1, &rfds, NULL, NULL, &tv);

   return !(retval == -1 || !retval);
}
//-----------------------------------------------------------------------------
bool hasNewEvents(std::vector<uint32_t> fileDescriptors, int64_t waitTime)
{
   //set time
   timeval tv;
   if(waitTime/1000 > numeric_limits<int32_t>::max())
      throw "specified time is too large";
   tv.tv_sec = waitTime/1000;
   tv.tv_usec = (waitTime%1000)*1000;

   //add the socket of this client to the set on which select will listen
   fd_set rfds;
   FD_ZERO(&rfds);
   for(uint32_t i=0; i<fileDescriptors.size(); i++)
      FD_SET(fileDescriptors[i], &rfds);
   int retval = select(fileDescriptors[fileDescriptors.size()-1]+1, &rfds, NULL, NULL, &tv);

   return !(retval == -1 || !retval);
}
//-----------------------------------------------------------------------------
uint64_t getMemorySizeInBytes()
{
   // first line should look like this: MemTotal:       1056859000 kB
   ifstream in("/proc/meminfo", ios::in);
   string ignore;
   uint64_t maxMemory;
   in >> ignore >> maxMemory;
   return maxMemory;
}
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
