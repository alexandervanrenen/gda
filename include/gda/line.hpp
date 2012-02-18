#ifndef GDA_LINE_HPP
#define GDA_LINE_HPP
//---------------------------------------------------------------------------
#include "gda/vector2.hpp"
#include <ostream>
#include <vector>
//---------------------------------------------------------------------------
// Utilities - line lib
// Alexander van Renen 2012
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
class Line {
public:
   /// ctor, the direction of a line may not be (0,0)
   Line(const Vector2<float>& a, const Vector2<float>& d);

   /// two identic lines are parallel aswell
   bool isParallel(const Line& other) const;
   bool isIdentic(const Line& other) const;

   /// ture is returned iff the lines intersect .. alpha and beta will be set to the scalars needed to calculate the intersection point .. if the lines are equal alpha==beta==0
   bool intersect(float& alpha, float& beta, const Line& other) const;

   /// calculates a point on the line
   const Vector2<float> evaluate(float alpha) const;

   /// print
   friend std::ostream& operator<< (std::ostream& os, const Line& line);

   /// get line with right angle
   Line rightAngleLine() const;

   /// sort points as if they where on the line
   std::vector<uint32_t> sortAlongLine(std::vector<Vector2<float> >& points) const;

   /// set the precision
   static const uint32_t precision = 3; // 3 decimal places are taken into account

   /// setter and getter
   void setUpPoint(const Vector2<float>& p);
   const Vector2<float> getUpPoint();
   void setDirection(const Vector2<float>& p);
   const Vector2<float> getDirection();

private:
   Vector2<float> a;
   Vector2<float> d;
};
//---------------------------------------------------------------------------
} // end of namespace gda
//---------------------------------------------------------------------------
#endif
