#ifndef GDA_VECTOR3_HPP
#define GDA_VECTOR3_HPP
//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdint.h>
#include <string>
//---------------------------------------------------------------------------
// Utilities - 3d vector
// Alexander van Renen 2010, 2011
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
template <class T>
struct Vector3 {
   
   /// Ctor
   explicit Vector3(const T& x=0, const T& y=0, const T& z=0);
   Vector3(const Vector3<T>& v);
   void operator=(const Vector3& v);

   /// Data access operators
   T& operator[](const uint32_t pos);
   const T& operator[](const uint32_t pos) const;

   /// Setters
   Vector3<T>& fill(const T& s);

   /// Math - modifies this vector
   Vector3<T>& add(const T& s);
   Vector3<T>& add(const Vector3<T>& v);

   Vector3<T>& sub(const T& s);
   Vector3<T>& sub(const Vector3<T>& v);

   Vector3<T>& div(const T& s);
   Vector3<T>& mul(const T& s);

   Vector3<T>& normalize(float length = 1.0f);

   Vector3<T>& inverse();
   Vector3<T>& absolute();

   /// Math - creats new vectors
   Vector3<T> operator+(const Vector3<T>& v) const;
   Vector3<T> operator-(const Vector3<T>& v) const;

   Vector3<T> cross(const Vector3<T>& v) const;

   T dot(const Vector3<T>& v) const;
   T dot() const; //secound vector is this

   float length() const;

   /// Output functions
   std::string toString() const;
   template<class S> friend std::ostream& operator<<(std::ostream& os, const Vector3<S>& v);

   /// Data
   union {
      struct { T x, y, z; };
      struct { T s, t, r; };
      T data[3];
   };
};
//---------------------------------------------------------------------------
template <class T>
Vector3<T>::Vector3(const T& x, const T& y, const T& z)
: x(x), y(y), z(z)
{
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>::Vector3(const Vector3<T>& v)
{
   for(uint8_t i=0; i<3; i++)
      data[i] = v.data[i];
}
//---------------------------------------------------------------------------
template <class T>
void Vector3<T>::operator=(const Vector3<T>& v)
{
   for(uint8_t i=0; i<3; i++)
      data[i] = v.data[i];
}
//---------------------------------------------------------------------------
template <class T>
T& Vector3<T>::operator[](const uint32_t pos)
{
   return data[pos];
}
//---------------------------------------------------------------------------
template <class T>
const T& Vector3<T>::operator[](const uint32_t pos) const
{
   return data[pos];
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::fill(const T& s)
{
   for(uint8_t i=0; i<3; i++)
      data[i] = s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::add(const T& s)
{
   for(uint8_t i=0; i<3; i++)
      data[i] += s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::add(const Vector3<T>& v)
{
   for(uint8_t i=0; i<3; i++)
      data[i] += v.data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::sub(const T& s)
{
   for(uint8_t i=0; i<3; i++)
      data[i] -= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::sub(const Vector3<T>& v)
{
   for(uint8_t i=0; i<3; i++)
      data[i] -= v.data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::div(const T& s)
{
   assert(s != static_cast<T>(0));
   for(uint8_t i=0; i<3; i++)
      data[i] /= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::mul(const T& s)
{
   for(uint8_t i=0; i<3; i++)
      data[i] *= s;
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::normalize(float length)
{
   assert(length != static_cast<T>(0));
   float l = this->length()/length;
   for(uint8_t i=0; i<3; i++)
      data[i] /= static_cast<T>(l);
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::inverse()
{
   for(uint8_t i=0; i<3; i++)
      data[i] = -data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::absolute()
{
   for(uint8_t i=0; i<3; i++)
      if(data[i]< static_cast<T>(0))
         data[i] = -data[i];
   return *this;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const
{
   Vector3<T> result(*this);
   for(uint8_t i=0; i<3; i++)
      result[i] += v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
{
   Vector3<T> result(*this);
   for(uint8_t i=0; i<3; i++)
      result[i] -= v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& v) const
{
   return Vector3<T>(
      this->data[1]*v.data[2] - this->data[2]*v.data[1],
      this->data[2]*v.data[0] - this->data[0]*v.data[2],
      this->data[0]*v.data[1] - this->data[1]*v.data[0]);
}
//---------------------------------------------------------------------------
template <class T>
T Vector3<T>::dot(const Vector3<T>& v) const
{
   T result = 0;
   for(uint8_t i=0; i<3; i++)
      result += data[i]*v.data[i];
   return result;
}
//---------------------------------------------------------------------------
template <class T>
T Vector3<T>::dot() const
{
   return dot(*this);
}
//---------------------------------------------------------------------------
template <class T>
float Vector3<T>::length() const
{
   T result = static_cast<T>(0);
   for(uint8_t i=0; i<3; i++)
      result += data[i]*data[i];
   return sqrt(result);
}
//---------------------------------------------------------------------------
template <class T>
std::string Vector3<T>::toString() const
{
   std::ostringstream os;
   os << "[" << data[0];
   for(uint8_t i=1; i<3; i++)
      os << "|" << data[i];
   os << "]";
   return os.str();
}
//---------------------------------------------------------------------------
template<class S>
std::ostream& operator<<(std::ostream& os, const Vector3<S>& v)
{
   os << v.toString();
   return os;
}
//---------------------------------------------------------------------------
} // end of namesapce gda
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
