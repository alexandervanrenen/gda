#ifndef GDA_VECTOR2_HPP
#define GDA_VECTOR2_HPP
//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdint.h>
#include <string>
//---------------------------------------------------------------------------
// Utilities - 2d vector
// Alexander van Renen 2010, 2011
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
template <class T>
struct Vector2 {
   
   /// Ctor
   Vector2(const T& x=0, const T& y=0);
   Vector2(const Vector2<T>& v);
   void operator=(const Vector2& v);

   /// Data access operators
   T& operator[](const uint32_t pos);
   const T& operator[](const uint32_t pos) const;

   /// Setters
   Vector2<T>& fill(const T& s);

   /// Math - modifies this vector
   Vector2<T>& add(const T& s);
   Vector2<T>& add(const Vector2<T>& v);

   Vector2<T>& sub(const T& s);
   Vector2<T>& sub(const Vector2<T>& v);

   Vector2<T>& div(const T& s);
   Vector2<T>& mul(const T& s);

   Vector2<T>& normalize(float length = 1.0f);

   Vector2<T>& inverse();
   Vector2<T>& absolute();

   /// Math - creats new vectors
   Vector2<T> operator+(const Vector2<T>& v) const;
   Vector2<T> operator-(const Vector2<T>& v) const;

   Vector2<T> cross(const Vector2<T>& v) const;

   T dot(const Vector2<T>& v) const;
   T dot() const; //secound vector is this

   float length() const;

   /// Output functions
   std::string toString() const;
   template<class S> friend std::ostream& operator<<(std::ostream& os, const Vector2<S>& v);

   /// Data
   union {
      struct { T x, y; };
      struct { T s, t; };
      T data[2];
   };
};
//---------------------------------------------------------------------------
template <class T>
Vector2<T>::Vector2(const T& x, const T& y)
: x(x), y(y)
{
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>::Vector2(const Vector2<T>& v)
{
   for(uint8_t i=0; i<2; i++)
      data[i] = v.data[i];
}
//---------------------------------------------------------------------------
template <class T>
void Vector2<T>::operator=(const Vector2<T>& v)
{
   for(uint8_t i=0; i<2; i++)
      data[i] = v.data[i];
}
//---------------------------------------------------------------------------
template <class T>
T& Vector2<T>::operator[](const uint32_t pos)
{
   return data[pos];
}
//---------------------------------------------------------------------------
template <class T>
const T& Vector2<T>::operator[](const uint32_t pos) const
{
   return data[pos];
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::fill(const T& s)
{
   for(uint8_t i=0; i<2; i++)
      data[i] = s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::add(const T& s)
{
   for(uint8_t i=0; i<2; i++)
      data[i] += s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::add(const Vector2<T>& v)
{
   for(uint8_t i=0; i<2; i++)
      data[i] += v.data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::sub(const T& s)
{
   for(uint8_t i=0; i<2; i++)
      data[i] -= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::sub(const Vector2<T>& v)
{
   for(uint8_t i=0; i<2; i++)
      data[i] -= v.data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::div(const T& s)
{
   assert(s != static_cast<T>(0));
   for(uint8_t i=0; i<2; i++)
      data[i] /= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::mul(const T& s)
{
   for(uint8_t i=0; i<2; i++)
      data[i] *= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::normalize(float length)
{
   assert(length != static_cast<T>(0));
   float l = this->length()/length;
   for(uint8_t i=0; i<2; i++)
      data[i] /= static_cast<T>(l);
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::inverse()
{
   for(uint8_t i=0; i<2; i++)
      data[i] = -data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::absolute()
{
   for(uint8_t i=0; i<2; i++)
      if(data[i]< static_cast<T>(0))
         data[i] = -data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const
{
   Vector2<T> result(*this);
   for(uint8_t i=0; i<2; i++)
      result[i] += v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const
{
   Vector2<T> result(*this);
   for(uint8_t i=0; i<2; i++)
      result[i] -= v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
Vector2<T> Vector2<T>::cross(const Vector2<T>& v) const
{
   return Vector2<T>(
      this->data[0]*v.data[1] - this->data[1]*v.data[0],
      this->data[1]*v.data[0] - this->data[0]*v.data[1]);
}
//---------------------------------------------------------------------------
template <class T>
T Vector2<T>::dot(const Vector2<T>& v) const
{
   T result = 0;
   for(uint8_t i=0; i<2; i++)
      result += data[i]*v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
T Vector2<T>::dot() const
{
   return dot(*this);
}
//---------------------------------------------------------------------------
template <class T>
float Vector2<T>::length() const
{
   T result = static_cast<T>(0);
   for(uint8_t i=0; i<2; i++)
      result += data[i]*data[i];
   return sqrt(result);
}
//---------------------------------------------------------------------------
template <class T>
std::string Vector2<T>::toString() const
{
   std::ostringstream os;
   os << "[" << data[0];
   for(uint8_t i=1; i<2; i++)
      os << "|" << data[i];
   os << "]";
   return os.str();
}
//---------------------------------------------------------------------------
template<class S>
std::ostream& operator<<(std::ostream& os, const Vector2<S>& v)
{
   os << v.toString();
   return os;
}
//---------------------------------------------------------------------------
} // end of namesapce gda
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
