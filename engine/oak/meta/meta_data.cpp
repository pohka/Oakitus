#include "meta_data.h"

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

Var* MetaData::getKV(const std::string& key)
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
  for (MetaKV* kv : lhs.kvs)
  {
    delete kv;
  }
  lhs.kvs.clear();

  lhs.selector = selector;
  for (MetaKV* kv : kvs)
  {
    unsigned char type = kv->var->getType();

    if (type == VAR_TYPE_STRING)
    {
      std::string val = static_cast<VarString*>(kv->var)->val;
      lhs.addKV(kv->getKey(), val, VAR_TYPE_STRING);
    }
  }
}

void MetaData::addKV(const std::string& key, const std::string& val, unsigned char type)
{
  if (type == VAR_TYPE_STRING)
  {
    VarString* var = new VarString(val);
    MetaKV* kv = new MetaKV(key, var);
    kvs.push_back(kv);
  }
}