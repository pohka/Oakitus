#ifndef META_VARS_H
#define META_VARS_H

#include "meta_def.h"

namespace oak
{
  struct Var
  {
    Var(unsigned char type = VAR_TYPE_NULL)
    {
      this->type = type;
    }

    ~Var()
    {

    }

    unsigned char getType()
    {
      return type;
    }

  private:
    unsigned char type = 0;
  };

  struct VarString : public Var
  {
    std::string val;

    VarString(std::string val) : Var(VAR_TYPE_STRING)
    {
      this->val = val;
    }

    ~VarString()
    {

    }

    static std::string get(Var* var)
    {

      if (var != nullptr && var->getType() == VAR_TYPE_STRING)
      {
        return static_cast<VarString*>(var)->val;
      }

      return "";
    }

    void copy(VarString& lhs)
    {
      lhs.val = this->val;
    }
  };

  struct VarNumber : public Var
  {
    float val;

    VarNumber(float val) : Var(VAR_TYPE_NUMBER)
    {
      this->val = val;
    }

    static float get(Var* var)
    {
      if (var != nullptr && var->getType() == VAR_TYPE_NUMBER)
      {
        return static_cast<VarNumber*>(var)->val;
      }

      return 0.0f;
    }

    void copy(VarNumber& lhs)
    {
      lhs.val = this->val;
    }
  };
}

#endif