#include "gda/utility.hpp"
#include <unistd.h>
#include <cstdlib>
//-----------------------------------------------------------------------------
// Utilities - general helper funtions
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
bool hasNewEvents(uint32_t fileDescriptor)
{
   //set time
   timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 0;

   //add the socket of this client to the set on which select will listen
   fd_set rfds;
   FD_ZERO(&rfds);
   FD_SET(fileDescriptor, &rfds);
   int retval = select(fileDescriptor+1, &rfds, NULL, NULL, &tv);

   return !(retval == -1 || !retval);
}
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
