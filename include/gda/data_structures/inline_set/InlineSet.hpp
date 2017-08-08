//
// This file is part of the gda cpp utility library.
// Copyright (c) 2017 Alexander van Renen. All rights reserved.
//
// Purpose - A set which stores data inline up to a given size
// -------------------------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------------------------
#include <string>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <cstring>
// -------------------------------------------------------------------------------------------------
#ifndef likely
#define likely(x)       __builtin_expect((x),1)
#endif
#ifndef unlikely
#define unlikely(x)     __builtin_expect((x),0)
#endif
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
template<class T, uint16_t kInplaceCapacity>
class InlineSet {
   union {
      T _inplace[kInplaceCapacity];
      T *_ptr;
   };

   uint16_t size_;
   uint16_t capacity_;

public:
   InlineSet()
           : size_(0)
             , capacity_(0)
   {
   }

   ~InlineSet()
   {
      if (capacity_>=kInplaceCapacity) {
         free(_ptr);
      }
   }

   InlineSet(InlineSet &&other)
   {
      memcpy(_inplace, other._inplace, kInplaceCapacity * sizeof(T));
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.size_ = 0;
      other.capacity_ = kInplaceCapacity;
   }

   InlineSet &operator=(InlineSet &&other)
   {
      memcpy(_inplace, other._inplace, kInplaceCapacity * sizeof(T));
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.size_ = 0;
      other.capacity_ = kInplaceCapacity;
      return *this;
   }

   void insert(T t)
   {
      // Find insert position & check if already there
      T *ptr = capacity_<=kInplaceCapacity ? _inplace : _ptr;
      uint16_t insertPos;
      for (insertPos = 0; insertPos<size_; insertPos++) { // Find insert pos // TODO maybe bin search
         if (ptr[insertPos] == t) // No duplicates
            return;
         if (ptr[insertPos]>t)
            break;
      }

      // Alloc new mem ?
      if (unlikely(size_>=capacity_ && size_>=kInplaceCapacity)) {
         if (capacity_ == 0) {
            capacity_ = kInplaceCapacity * uint16_t(2);
            T *tmp = (T *) malloc(capacity_ * sizeof(T));
            memcpy(tmp, _inplace, size_ * sizeof(T));
            _ptr = tmp;
         } else {
            capacity_ = capacity_ * uint16_t(2);
            _ptr = (T *) realloc(_ptr, capacity_ * sizeof(T));
         }
         ptr = _ptr;
      }

      // Insert element
      memmove(ptr + insertPos + 1, ptr + insertPos, (size_ - insertPos) * sizeof(T)); // Shift everything else to the right
      ptr[insertPos] = t; // Insert
      size_++;
   }

   bool contains(T t)
   {
      // Search content
      T *ptr = capacity_<=kInplaceCapacity ? _inplace : _ptr;
      uint16_t insertPos;
      for (insertPos = 0; insertPos<size_; insertPos++) { // Find insert pos // TODO maybe bin search
         if (ptr[insertPos] == t) // No duplicates
            return true;
         if (ptr[insertPos]>t)
            break;
      }
      return false;
   }

   void erase(T t)
   {
      T *ptr = capacity_<=kInplaceCapacity ? _inplace : _ptr;
      uint16_t removePos;
      for (removePos = 0; removePos<size_; removePos++) { // Find insert pos // TODO maybe bin search
         if (t == ptr[removePos])
            break;
      }
      if (removePos == size_)
         return;

      if (removePos + 1<size_) // No need to copy when we remove the last element
         memmove(ptr + removePos, ptr + removePos + 1, (size_ - removePos - 1) * sizeof(T)); // Shift everything else to the left
      size_--;
   }

   uint32_t size() const
   {
      return size_;
   }

   T get(uint32_t pos)
   {
      T *ptr = capacity_<=kInplaceCapacity ? _inplace : _ptr;
      return ptr[pos];
   }

   std::vector<T> toVector()
   {
      T *ptr = capacity_<=kInplaceCapacity ? _inplace : _ptr;
      std::vector<T> res(size_);
      memcpy(res.data(), ptr, size_ * sizeof(T));
      return res;
   }

   void destroy_debug()
   {
      if (capacity_>=kInplaceCapacity) {
         free(_ptr);
      }
      capacity_ = 0;
      size_ = 0;
   }
};
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
