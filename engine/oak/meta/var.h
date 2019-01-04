#ifndef VAR_H
#define VAR_H

#include <string>
#include "var_base.h"

namespace oak
{
  struct var : public var_base
  {
    //constructors
    var();
    var(const var& v);
    var(const std::string& str, const unsigned char type);

    //set
    void set(const std::string& str, const unsigned char type);

    //casting
    const float toNumber() const;
    const int toInt() const;
    const std::string & toString() const;
    const bool toBool() const;

  private:
    std::string str;
  };
}

#endif