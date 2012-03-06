#ifndef GDA_UTILITY_HPP
#define GDA_UTILITY_HPP
//-----------------------------------------------------------------------------
#include <memory>
//-----------------------------------------------------------------------------
// Utilities - general helper funtions
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
namespace gda {
/// creates a unique ptr
template<class T, class... Arg>
std::unique_ptr<T> make_unique(Arg&& ...args)
{
   return std::unique_ptr<T>(new T(std::forward<Arg>(args)...));
}
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
