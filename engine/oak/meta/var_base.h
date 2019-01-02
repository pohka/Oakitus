#ifndef VAR_BASE_H
#define VAR_BASE_H

namespace oak
{
  struct var_base
  {
    //returns the type
    const unsigned char getType() const
    {
      return type;
    }

  protected:
    unsigned char type;
  };
}

#endif
