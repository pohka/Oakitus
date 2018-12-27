#ifndef META_DATA_H
#define META_DATA_H

#include <string>
#include <vector>
#include <iostream>

namespace oak
{

  const unsigned char VAR_TYPE_NULL = 0;
  const unsigned char VAR_TYPE_STRING = 1;
  const unsigned char VAR_TYPE_NUMBER = 2;
  const unsigned char VAR_TYPE_ARRAY = 3;

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

    protected:
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

    static std::string toString(Var* var)
    {
      if (var->getType() == VAR_TYPE_STRING)
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

  struct MetaKV
  {
    MetaKV(const std::string key, Var* var)
    {
      this->key = key;
      this->var = var;
    }

    ~MetaKV()
    {
      if (var != nullptr && var->getType() != VAR_TYPE_NULL)
      {
        std::cout << "tpye:" << var->getType();
        delete var;
      }
    }

    const std::string& getKey() const
    {
      return key;
    }

    Var* var = nullptr;

    private:
      std::string key;
  };

  struct MetaData
  {
    static const Var VAR_NULL;

    MetaData();
    ~MetaData();

    std::string selector;
    

    void addKV(const std::string& key, const std::string& val, unsigned char type);

    //get var by key, if not found then an empty string is returned
    Var* getKV(const std::string& key);

    //makes a deep copy and outputs to rhs
    void copy(MetaData& rhs);

  private:
    std::vector<MetaKV*> kvs;
  };
}

#endif