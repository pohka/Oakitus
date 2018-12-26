#include "meta_data.h"

using namespace oak;


std::string MetaData::get(const std::string& key)
{
  for (unsigned int i = 0; i < kvs.size(); i++)
  {
    if (kvs[i].key == key)
    {
      return kvs[i].val;
    }
  }

  return "";
}


void MetaData::copy(MetaData& rhs)
{
  rhs.selector = selector;
  rhs.kvs.clear();
  for (unsigned int i = 0; i < kvs.size(); i++)
  {
    rhs.kvs.push_back({ kvs[i].key, kvs[i].val });
  }
}