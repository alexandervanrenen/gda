#ifndef GDA_VECTOR4_HPP
#define GDA_VECTOR4_HPP
//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdint.h>
#include <string>
//---------------------------------------------------------------------------
// Utilities - 4d vector
// Alexander van Renen 2010, 2011
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
template <class T>
struct Vector4 {
   
   /// Ctor
   explicit Vector4(const T& x=0, const T& y=0, const T& z=0, const T& w=0);
   explicit Vector4(const Vector4<T>& v);
   void operator=(const Vector4& v);
   template<class U>
   Vector4(const Vector4<U>& o);
   template<class U>
   void operator=(const Vector4<U>& o);

   /// Data access operators
   T& operator[](const uint32_t pos);
   const T& operator[](const uint32_t pos) const;

   /// Setters
   Vector4<T>& fill(const T& s);

   /// Math - modifies this vector
   Vector4<T>& add(const T& s);
   Vector4<T>& add(const Vector4<T>& v);

   Vector4<T>& sub(const T& s);
   Vector4<T>& sub(const Vector4<T>& v);

   Vector4<T>& div(const T& s);
   Vector4<T>& mul(const T& s);

   Vector4<T>& normalize(float length = 1.0f);

   Vector4<T>& inverse();
   Vector4<T>& absolute();

   /// Math - creats new vectors
   Vector4<T> operator+(const Vector4<T>& v) const;
   Vector4<T> operator-(const Vector4<T>& v) const;

   Vector4<T> cross(const Vector4<T>& v) const;

   T dot(const Vector4<T>& v) const;
   T dot() const; //secound vector is this

   float length() const;

   /// Equality
   bool operator== (const Vector4<T>& v) const;
   bool operator!= (const Vector4<T>& v) const;

   /// Output functions
   std::string toString() const;
   template<class S> friend std::ostream& operator<<(std::ostream& os, const Vector4<S>& v);

   /// Data
   union {
      struct { T x, y, z, w; };
      struct { T x1, x2, x3, x4; };
      T data[4];
   };
};
//---------------------------------------------------------------------------
template <class T>
Vector4<T>::Vector4(const T& x, const T& y, const T& z, const T& w)
: x(x), y(y), z(z), w(w)
{
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>::Vector4(const Vector4<T>& v)
{
   for(uint8_t i=0; i<4; i++)
      data[i] = v.data[i];
}
//---------------------------------------------------------------------------
template <class T>
void Vector4<T>::operator=(const Vector4<T>& v)
{
   for(uint8_t i=0; i<4; i++)
      data[i] = v.data[i];
}
//---------------------------------------------------------------------------
template <class T>
template <class U>
Vector4<T>::Vector4(const Vector4<U>& o)
{
   for(uint8_t i=0; i<4; i++)
      data[i] = o.data[i];
}
//---------------------------------------------------------------------------
template <class T>
template <class U>
void Vector4<T>::operator=(const Vector4<U>& o)
{
   for(uint8_t i=0; i<4; i++)
      data[i] = o.data[i];
}
//---------------------------------------------------------------------------
template <class T>
T& Vector4<T>::operator[](const uint32_t pos)
{
   return data[pos];
}
//---------------------------------------------------------------------------
template <class T>
const T& Vector4<T>::operator[](const uint32_t pos) const
{
   return data[pos];
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::fill(const T& s)
{
   for(uint8_t i=0; i<4; i++)
      data[i] = s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::add(const T& s)
{
   for(uint8_t i=0; i<4; i++)
      data[i] += s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::add(const Vector4<T>& v)
{
   for(uint8_t i=0; i<4; i++)
      data[i] += v.data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::sub(const T& s)
{
   for(uint8_t i=0; i<4; i++)
      data[i] -= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::sub(const Vector4<T>& v)
{
   for(uint8_t i=0; i<4; i++)
      data[i] -= v.data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::div(const T& s)
{
   assert(s != static_cast<T>(0));
   for(uint8_t i=0; i<4; i++)
      data[i] /= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::mul(const T& s)
{
   for(uint8_t i=0; i<4; i++)
      data[i] *= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::normalize(float length)
{
   assert(length != static_cast<T>(0));
   float l = this->length()/length;
   for(uint8_t i=0; i<4; i++)
      data[i] /= static_cast<T>(l);
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::inverse()
{
   for(uint8_t i=0; i<4; i++)
      data[i] = -data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T>& Vector4<T>::absolute()
{
   for(uint8_t i=0; i<4; i++)
      if(data[i]< static_cast<T>(0))
         data[i] = -data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& v) const
{
   Vector4<T> result(*this);
   for(uint8_t i=0; i<4; i++)
      result[i] += v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& v) const
{
   Vector4<T> result(*this);
   for(uint8_t i=0; i<4; i++)
      result[i] -= v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
Vector4<T> Vector4<T>::cross(const Vector4<T>& v) const
{
   assert(false && "cross product not available on 4d vectors");
   throw;
}
//---------------------------------------------------------------------------
template <class T>
T Vector4<T>::dot(const Vector4<T>& v) const
{
   T result = 0;
   for(uint8_t i=0; i<4; i++)
      result += data[i]*v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
T Vector4<T>::dot() const
{
   return dot(*this);
}
//---------------------------------------------------------------------------
template <class T>
float Vector4<T>::length() const
{
   T result = static_cast<T>(0);
   for(uint8_t i=0; i<4; i++)
      result += data[i]*data[i];
   return sqrt(result);
}
//---------------------------------------------------------------------------
template <class T>
bool Vector4<T>::operator== (const Vector4<T>& v) const
{
   return x==v.x && y==v.y && z==v.z && data[3]==v.data[3];
}
//---------------------------------------------------------------------------
template <class T>
bool Vector4<T>::operator!= (const Vector4<T>& v) const
{
   return x!=v.x || y!=v.y || z!=v.z || data[3]!=v.data[3];
}
//---------------------------------------------------------------------------
template <class T>
std::string Vector4<T>::toString() const
{
   std::ostringstream os;
   os << "[" << data[0];
   for(uint8_t i=1; i<4; i++)
      os << "|" << data[i];
   os << "]";
   return os.str();
}
//---------------------------------------------------------------------------
template<class S>
std::ostream& operator<<(std::ostream& os, const Vector4<S>& v)
{
   os << v.toString();
   return os;
}
//---------------------------------------------------------------------------
} // end of namesapce gda
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
