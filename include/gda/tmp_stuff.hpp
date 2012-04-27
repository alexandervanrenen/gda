#ifndef GDA_TMP_STUFF_HPP
#define GDA_TMP_STUFF_HPP
//-----------------------------------------------------------------------------
// Utilities - template metaprogramming stuff
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
/// static if
template<bool flag, class A, class B>
struct StaticIf {
   typedef B type;
};
template<class A, class B>
struct StaticIf<true, A, B> {
   typedef A type;
};
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
