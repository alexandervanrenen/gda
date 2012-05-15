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
//-----------------------------------------------------------------------------
#if defined __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus == 201103L
//-----------------------------------------------------------------------------
/// creates a unique ptr (only c++11)
template<class T, class... Arg>
std::unique_ptr<T> make_unique(Arg&& ...args)
{
   return std::unique_ptr<T>(new T(std::forward<Arg>(args)...));
}
//-----------------------------------------------------------------------------
/// get tail of a tuple
template<typename Head, typename... Tail>
std::tuple<Tail...> getTypeOfHead(const std::tuple<Head, Tail...>&)
{
   return std::tuple<Tail...>();
}
template<uint32_t i, typename Extra, typename... T>
typename std::enable_if<i==0>::type copyTail(std::tuple<T...>&, const std::tuple<Extra, T...>&)
{
}
template<uint32_t i, typename Extra, typename... T>
typename std::enable_if<i>=1>::type copyTail(std::tuple<T...>& t, const std::tuple<Extra, T...>& f)
{
   std::get<i-1>(t) = std::get<i>(f);
   copyTail<i-1, Extra, T...>(t, f);
}
template<typename... T>
auto tail(const std::tuple<T...>& t) -> decltype(getTypeOfHead(t))
{
   decltype(getTypeOfHead(t)) result;
   copyTail<std::tuple_size<decltype(getTypeOfHead(t))>::value, T...>(result, t);
   return result;
}
//-----------------------------------------------------------------------------
/// helper functions to read a tuple from std::istream
template<uint32_t pos, typename... T>
   typename std::enable_if<pos>=sizeof...(T)>::type readTuple(std::istream&, std::tuple<T...>&) {}
template<uint32_t pos, typename... T>
   typename std::enable_if<pos<sizeof...(T)>::type readTuple(std::istream& is, std::tuple<T...>& t) { is >> std::get<pos>(t); readTuple<pos+1>(is, t);}
template<typename... T>
   void readTuple(std::istream& is, std::tuple<T...>& t) { readTuple<0, T...>(is, t);}
//-----------------------------------------------------------------------------
/// helper functions to write a tuple to std::ostream
template<uint32_t pos, typename... T>
   typename std::enable_if<pos>=sizeof...(T)>::type writeTuple(std::ostream&, const std::tuple<T...>&) {}
template<uint32_t pos, typename... T>
   typename std::enable_if<pos<sizeof...(T)>::type writeTuple(std::ostream& os, const std::tuple<T...>& t) { os << std::get<pos>(t) << " "; writeTuple<pos+1, T...>(os, t);}
template<typename... T>
   void writeTuple(std::ostream& os, const std::tuple<T...>& t) { writeTuple<0, T...>(os, t);}
//-----------------------------------------------------------------------------
#endif // end of c++11 stuff
//-----------------------------------------------------------------------------
/// check if there is new input on the file descriptor
bool hasNewEvents(uint32_t fileDescriptor);
/// trys to figure out currenty memory
uint64_t getMemorySizeInBytes();
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
