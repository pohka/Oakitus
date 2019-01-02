#ifndef VAR_OBJECT_H
#define VAR_OBJECT_H

#include "var_base.h"
#include "kvmap.h"
#include <string>
#include "var.h"

namespace oak
{
  //object of vars
  struct var_object : public var_base
  {
    var_object();

    //get var by key if var type is not a primitive type it returns nullptr
    var* getVar(const std::string& key);

    //get var_object by key , if var type is not object it returns nullptr
    var_object* getObj(const std::string& key);

    //key values
    kvmap<std::string, var_base*> kvs;
  };
}

#endif