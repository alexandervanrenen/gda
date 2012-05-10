#ifndef GDA_UTILITY_HPP
#define GDA_UTILITY_HPP
//-----------------------------------------------------------------------------
#include <memory>
#include <stdint.h>
//-----------------------------------------------------------------------------
// Utilities - general helper funtions
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
namespace gda {
#if defined __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus == 201103L
/// creates a unique ptr (only c++11)
template<class T, class... Arg>
std::unique_ptr<T> make_unique(Arg&& ...args)
{
   return std::unique_ptr<T>(new T(std::forward<Arg>(args)...));
}
#endif

/// check if there is new input on the file descriptor
bool hasNewEvents(uint32_t fileDescriptor);
/// trys to figure out currenty memory
uint64_t getMemorySizeInBytes();
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
