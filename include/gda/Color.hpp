//
// This file is part of the gda cpp utility library.
// Copyright (c) 2012 Alexander van Renen. All rights reserved.
//
// Purpose - Represents a RBG color
// -------------------------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------------------------
#include <string>
#include <stdint.h>
#include <iostream>
// -------------------------------------------------------------------------------------------------
namespace gda {
// -------------------------------------------------------------------------------------------------
enum struct Color : uint8_t { Red, Green, Blue, Black, White };
// -------------------------------------------------------------------------------------------------
namespace ColorHelper {
// -------------------------------------------------------------------------------------------------
/// Transforms a string into a color
Color stringToType(const std::string& colorName);
// -------------------------------------------------------------------------------------------------
} // End of namespace ColorHelper
// -------------------------------------------------------------------------------------------------
struct ColorRGB {
   /// Constructor
   explicit ColorRGB(Color type = Color::Black);
   explicit ColorRGB(const std::string& hexStr);
   explicit ColorRGB(uint8_t red, uint8_t green, uint8_t blue);

   /// Modifiers
   void change(Color type);
   void change(const std::string& hexStr);
   void change(uint8_t red, uint8_t green, uint8_t blue);

   /// Properties
   union { uint8_t red; uint8_t r; };
   union { uint8_t green; uint8_t g; };
   union { uint8_t blue; uint8_t b; };

   /// To string
   const std::string str() const;
   uint32_t integer() const;
private:
   static uint8_t hexDigitToInt(char c);
};
// TODO: Add ColorRGBA
// -------------------------------------------------------------------------------------------------
} // End of namespace gda
// -------------------------------------------------------------------------------------------------
