#include "meta_data.h"
#include "meta_vars.h"
#include <iostream>

using namespace oak;

const Var MetaData::VAR_NULL = Var();

MetaData::MetaData()
{

}

MetaData::~MetaData()
{
  for (unsigned int i = 0; i < kvs.size(); i++)
  {
    delete kvs[i];
  }
}

Var* MetaData::findVar(const std::string& key)
{
  for (unsigned int i = 0; i < kvs.size(); i++)
  {
    if (kvs[i]->getKey() == key)
    {
      return kvs[i]->var;
    }
  }

  return nullptr;
}


void MetaData::copy(MetaData& lhs)
{
  for (MetaKV* lhsKV : lhs.kvs)
  {
    delete lhsKV;
  }
  lhs.kvs.clear();

  lhs.selector = selector;

  for (MetaKV* kv : kvs)
  {
    unsigned char type = kv->var->getType();

    if (type == VAR_TYPE_STRING)
    {
      std::string val = static_cast<VarString*>(kv->var)->val;
      VarString* var = new VarString(val);
      MetaKV* a = new MetaKV(kv->getKey(), var);
      lhs.addKV(a);
    }
    else if (type == VAR_TYPE_NUMBER)
    {
      float val = static_cast<VarNumber*>(kv->var)->val;
      VarNumber* var = new VarNumber(val);
      MetaKV* a = new MetaKV(kv->getKey(), var);
      lhs.addKV(a);
    }
  }
}

void MetaData::addKV(MetaKV* kv)
{
  kvs.push_back(kv);
}