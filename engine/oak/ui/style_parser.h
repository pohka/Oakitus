#pragma once
#ifndef STYLE_PARSER_H
#define STYLE_PARSER_H

#include <string>
#include <vector>

namespace ion
{
  struct StyleParser
  {
    //parses a string value into a float
    static bool parseNumber(const std::string& val, float& num);

    //parses a color string and converts them to floats and added to float vector
    //e.g. #fff, #ff00ff, rgba(0,255,0,255)
    static void parseColor(std::string& val, std::vector<float>& rgba);

    //convert hex string to decimal float, e.g. "ff" = 255.0f
    static float hexToDecimal(std::string& str);

    //convert hex char to decimal float, e.g. "f" = 15.0f
    static float hexToDecimal(char ch);

    static unsigned char parseStateID(std::string state);
  };
}

#endif