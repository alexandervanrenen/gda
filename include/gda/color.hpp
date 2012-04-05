#ifndef GDA_COLOR_HPP
#define GDA_COLOR_HPP
//---------------------------------------------------------------------------
#include <string>
#include <stdint.h>
#include <iostream>
//---------------------------------------------------------------------------
// Utilities - color class
// Alexander van Renen 2012
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
struct Color {

   enum Type {Red, Green, Blue, Black, Wite};

   /// constructor
   explicit Color(Type type = Black);
   explicit Color(const std::string& hexStr);
   explicit Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xff);
   
   /// modifiers
   void change(Type type);
   void change(const std::string& hexstr);
   void change(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xff);

   /// properties
   union { uint8_t red;   uint8_t r; };
   union { uint8_t green; uint8_t g; };
   union { uint8_t blue;  uint8_t b; };
   union { uint8_t alpha; uint8_t a; };

   /// helper function
   static Type stringToType(const std::string& colorName);

   /// print and read function
   friend std::ostream& operator<<(std::ostream& stream, const Color &color);
   friend std::istream& operator>>(std::istream& stream, Color &color);

private:
   static int hexDigitToInt(uint8_t a);
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
