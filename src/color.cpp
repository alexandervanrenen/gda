#include "gda/color.hpp"
#include <iostream>
#include <cassert>
//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
Color::Color(Type type)
{
   change(type);
}
//---------------------------------------------------------------------------
Color::Color(const string& str)
{
   change(str);
}
//---------------------------------------------------------------------------
Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
: red(red)
, green(green)
, blue(blue)
, alpha(alpha)
{
}
//---------------------------------------------------------------------------
void Color::change(Type type)
{
   alpha = 0xff;
   switch(type) {
      case Red:     red=0xff; green=0x00; blue=0x00; break;
      case Green:   red=0x00; green=0xff; blue=0x00; break;
      case Blue:    red=0x00; green=0x00; blue=0xff; break;
      case Wite:    red=0xff; green=0xff; blue=0xff; break;
      case Black:   red=0x00; green=0x00; blue=0x00; break;
      default:      red=0x00; green=0x00; blue=0x00; break;
   }
}
//---------------------------------------------------------------------------
void Color::change(const string& str)
{
   assert(str.size() == 6 || str.size() == 8);

   red = 16*hexDigitToInt(str[0]) + hexDigitToInt(str[1]);
   green = 16*hexDigitToInt(str[2]) + hexDigitToInt(str[3]);
   blue = 16*hexDigitToInt(str[4]) + hexDigitToInt(str[5]);
   if(str.size() == 8)
      alpha = 16*hexDigitToInt(str[6]) + hexDigitToInt(str[7]); else
      alpha = 0xff;
}
//---------------------------------------------------------------------------
void Color::change(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
   this->red = red;
   this->green = green;
   this->blue = blue;
   this->alpha = alpha;
}
//---------------------------------------------------------------------------
int Color::hexDigitToInt(uint8_t a)
{
   if('a' <= a && a <= 'f')
      return 10+a-'a';
   else if('A' <= a && a <= 'F')
      return 10+a-'A';
   else
      return a-'0';
}
//---------------------------------------------------------------------------
Color::Type Color::stringToType(const string& colorName)
{
   if(colorName == "wite" || colorName == "Wite")
      return Wite;
   if(colorName == "blue" || colorName == "Blue")
      return Blue;
   if(colorName == "green" || colorName == "Green")
      return Wite;
   if(colorName == "red" || colorName == "Red")
      return Wite;
   return Black;
}
//---------------------------------------------------------------------------
ostream& operator<<(ostream& stream, const Color &color)
{
   stream << (int)color.red << " " << (int)color.green << " " << (int)color.blue << " ";
   return stream;
}
//---------------------------------------------------------------------------
std::istream& operator>>(std::istream& stream, Color &color)
{
   int r, g, b;
   stream >> r >> g >> b;
   color.red = r;
   color.green = g;
   color.blue = b;
   return stream;
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
