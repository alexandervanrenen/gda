#ifndef GDA_GENERICALLOCATORPOLICIES_HPP
#define GDA_GENERICALLOCATORPOLICIES_HPP
//---------------------------------------------------------------------------
#include "GenericAllocatorPolicies.hpp"
#include <stdint.h>
#include <cassert>
//---------------------------------------------------------------------------
// Utilities - generic allocator policies
// Alexander van Renen 2012
//---------------------------------------------------------------------------
namespace gda {
/// host class => a customizable fast allocator
template<class T, template <class Type> class Allocator = FreeListPolicy, class LockPolicy = NoLockPolicy, class InheritenceSupport = AssertOnInheritencePolicy>
class GenericAllocator : public Allocator<T>, LockPolicy, InheritenceSupport {
public:

   static void* operator new(std::size_t size) throw(std::bad_alloc);

   static void operator delete(void* data, std::size_t size) throw();

protected:
   ~GenericAllocator() {}
};
//---------------------------------------------------------------------------
/// new operator of host class, combining the policies
template<class T, template <class> class Allocator, class LockPolicy, class InheritenceSupport>
void* GenericAllocator<T, Allocator, LockPolicy, InheritenceSupport>::operator new(std::size_t size) throw(std::bad_alloc)
{
   typename LockPolicy::Lock guard;

   if((sizeof(T)!=size))
      return InheritenceSupport::allocate(size);

   return Allocator<T>::allocate(size);
}
//---------------------------------------------------------------------------
/// delete operator of host class, combining the policies
template<class T, template <class Type> class Allocator, class LockPolicy, class InheritenceSupport>
void GenericAllocator<T, Allocator, LockPolicy, InheritenceSupport>::operator delete(void* data, std::size_t size) throw()
{
   typename LockPolicy::Lock guard;

   if((sizeof(T)!=size)) {
      InheritenceSupport::deallocate(data, size);
      return;
   }

   Allocator<T>::deallocate(data, size);
}
//---------------------------------------------------------------------------
} // end of namesapce gda
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
