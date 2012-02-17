#include "gda/line.hpp"
#include <iostream>
#include <algorithm>
//-----------------------------------------------------------------------------
// Utilities - line lib
// Alexander van Renen 2012
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace gda {
//-----------------------------------------------------------------------------
typedef Vector2<float> Vec2;
//-----------------------------------------------------------------------------
const float epsilon = 1.0f/(Line::precision+1);
//-----------------------------------------------------------------------------
Line::Line(const Vec2& a, const Vec2& d)
: a(a)
, d(d)
{
   assert(d != Vec2(0,0));
}
//---------------------------------------------------------------------------
bool Line::isParallel(const Line& o) const
{
   Vec2 nd = d;
   Vec2 nod = o.d;
   nd.normalize();
   nod.normalize();

   return nd==nod || nd.inverse()==nod;
}
//---------------------------------------------------------------------------
bool Line::isIdentic(const Line& o) const
{
   if(!isParallel(o))
      return false;
   if(d.x==0)
      return a.x - o.a.x < epsilon;
   if(d.y==0)
      return a.y-o.a.y < epsilon;
   
   return (o.a.x-a.x)/d.x - (o.a.y-a.y)/d.y < epsilon;
}
//-----------------------------------------------------------------------------
bool Line::intersect(float& alpha, float& beta, const Line& o) const
{
   // case 1: parallel
   alpha=0;
   beta=0;
   if(isIdentic(o))
      return true;
   if(isParallel(o))
      return false;

   // case 2: d.x==0
   if(d.x==0) {
      // we know: d.x==0 => d.y!=0 (otherwise d==(0,0) which is invalid) && o.d.x!=0 (otherwise this and o are parallel)
      beta = (a.x-o.a.x) / o.d.x;
      alpha = (o.a.y-a.y+beta*o.d.y) / d.y;
      return true;
   }

   // case 3: o.d.x==0
   if(o.d.x==0) {
      // we know: o.d.x==0 => o.d.y!=0 (otherwise o.d==(0,0) which is invalid) && d.x!=0 (otherwise this and o are parallel)
      alpha = (o.a.x-a.x) / d.x;
      beta = -(o.a.y-a.y-alpha*d.y) / o.d.y;
      return true;
   }

   // case 4: not any other case
   // we know: this and o are not parallel (case 1) && d.x!=0 (case 2) && o.d.x!=0 (case 3) => d.y*o.d.y-d.y*o.d.x != 0 (otherwise parallel)
   alpha = ((o.a.x-a.x)*o.d.y - (o.a.y-a.y)*o.d.x) / (d.x*o.d.y - d.y*o.d.x);
   beta = -(o.a.x-a.x-alpha*d.x) / o.d.x;
   return true;
}
//-----------------------------------------------------------------------------
const Vec2 Line::evaluate(float alpha) const
{
   return Vec2(a.x+d.x*alpha, a.y+d.y*alpha);
}
//-----------------------------------------------------------------------------
ostream& operator<< (ostream& os, const Line& line)
{
   os << line.a << "  " << line.d << endl;
   return os;
}
//-----------------------------------------------------------------------------
Line Line::rightAngleLine() const
{
   return Line(a, Vec2(-d.y,d.x));
}
//-----------------------------------------------------------------------------
void Line::sortAlongLine(vector<Vec2>& points) const
{
   // init
   vector<pair<float, Vec2>> result;
   Line rectLine = rightAngleLine();

   // calculate a scalar for each point describing its fitness
   for(auto iter : points) {
      rectLine.setUpPoint(iter);
      float alpha, beta;
      intersect(alpha, beta, rectLine);
      result.push_back(make_pair(alpha, iter));
   }

   // sort by fitness
   sort(result.begin(), result.end(), [](const pair<float, Vec2>& lhs, const pair<float, Vec2>& rhs){return lhs.first<rhs.first;});

   // write data back to points
   for(uint32_t i=0; i<points.size(); i++)
      points[i] = result[i].second;
}
//-----------------------------------------------------------------------------
void Line::setUpPoint(const Vec2& p)
{
   a = p;
}
//-----------------------------------------------------------------------------
const Vec2 Line::getUpPoint()
{
   return a;
}
//-----------------------------------------------------------------------------
void Line::setDirection(const Vec2& p)
{
   d = p;
}
//-----------------------------------------------------------------------------
const Vec2 Line::getDirection()
{
   return d;
}
//-----------------------------------------------------------------------------
} // end of namespace gda
//-----------------------------------------------------------------------------
