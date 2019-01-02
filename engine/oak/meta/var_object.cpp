#include "var_object.h"

using namespace oak;

var_object::var_object()
{
  type = VAR_OBJECT;
}

var* var_object::getVar(const std::string& key)
{
  var_base* v = kvs.at(key);
  if (v->getType() != VAR_OBJECT)
  {
    return static_cast<var*>(v);
  }
  return nullptr;
}

var_object* var_object::getObj(const std::string& key)
{
  var_base* v = kvs.at(key);
  if (v->getType() == VAR_OBJECT)
  {
    return static_cast<var_object*>(v);
  }
  return nullptr;
}