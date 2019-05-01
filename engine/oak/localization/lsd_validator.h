#pragma once
#ifndef LSD_VALIDATOR_H
#define LSD_VALIDATOR_H

#include <string>

namespace oak
{
  class LSDValidator
  {
  public:
    //prints warnings
    static bool validate(const std::string& path);
  };
}

#endif
