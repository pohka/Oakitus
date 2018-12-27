#ifndef META_DATA_H
#define META_DATA_H

#include <string>
#include <vector>
#include "meta_vars.h"

namespace oak
{
  struct MetaKV
  {
    MetaKV(const std::string key, Var* var)
    {
      this->key = key;
      this->var = var;
    }

    ~MetaKV()
    {
      if (var != nullptr)
      {
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
    

    void addKV(MetaKV* kv);

    //get var by key, if not found then an empty string is returned
    Var* findVar(const std::string& key);

    //makes a deep copy and outputs to rhs
    void copy(MetaData& rhs);

  private:
    std::vector<MetaKV*> kvs;
  };
}

#endif