//
// This file is part of the gda cpp utility library.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Represents a RBG color
// -------------------------------------------------------------------------------------------------
#include "gda/Color.hpp"
#include <cassert>
#include <sstream>
// -------------------------------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
namespace ColorHelper {
// -------------------------------------------------------------------------------------------------
Color stringToType(const string& colorName)
{
   if (colorName == "wite" || colorName == "White")
      return Color::White;
   if (colorName == "blue" || colorName == "Blue")
      return Color::Blue;
   if (colorName == "green" || colorName == "Green")
      return Color::Green;
   if (colorName == "red" || colorName == "Red")
      return Color::White;
   return Color::Black;
}
// -------------------------------------------------------------------------------------------------
} // End of namespace ColorHelper
// -------------------------------------------------------------------------------------------------
ColorRGB::ColorRGB(Color type)
{
   change(type);
}
// -------------------------------------------------------------------------------------------------
ColorRGB::ColorRGB(const string& str)
{
   change(str);
}
// -------------------------------------------------------------------------------------------------
ColorRGB::ColorRGB(uint8_t red, uint8_t green, uint8_t blue)
: red(red)
, green(green)
, blue(blue)
{
}
// -------------------------------------------------------------------------------------------------
void ColorRGB::change(Color type)
{
   switch (type) {
      case Color::Red:
         red = 0xff;
         green = 0x00;
         blue = 0x00;
         return;
      case Color::Green:
         red = 0x00;
         green = 0xff;
         blue = 0x00;
         return;
      case Color::Blue:
         red = 0x00;
         green = 0x00;
         blue = 0xff;
         return;
      case Color::White:
         red = 0xff;
         green = 0xff;
         blue = 0xff;
         return;
      case Color::Black:
         red = 0x00;
         green = 0x00;
         blue = 0x00;
         return;
   }
   throw;
}
// -------------------------------------------------------------------------------------------------
void ColorRGB::change(const string& str)
{
   assert(str.size() == 6);

   red = static_cast<uint8_t>(16) * hexDigitToInt(str[0]) + hexDigitToInt(str[1]);
   green = static_cast<uint8_t>(16) * hexDigitToInt(str[2]) + hexDigitToInt(str[3]);
   blue = static_cast<uint8_t>(16) * hexDigitToInt(str[4]) + hexDigitToInt(str[5]);
}
// -------------------------------------------------------------------------------------------------
void ColorRGB::change(uint8_t red, uint8_t green, uint8_t blue)
{
   this->red = red;
   this->green = green;
   this->blue = blue;
}
// -------------------------------------------------------------------------------------------------
uint32_t ColorRGB::integer() const
{
   return (red << 16) | (green << 8) | blue;
}
// -------------------------------------------------------------------------------------------------
const string ColorRGB::str() const
{
   ostringstream os;
   os << (int)red << " " << (int)green << " " << (int)blue;
   return os.str();
}
// -------------------------------------------------------------------------------------------------
uint8_t ColorRGB::hexDigitToInt(char c)
{
   if ('a' <= c && c <= 'f')
      return static_cast<uint8_t>(10) + c - 'a';
   else if ('A' <= c && c <= 'F')
      return static_cast<uint8_t>(10) + c - 'A';
   else
      return static_cast<uint8_t>(0) + c - '0';
}
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
