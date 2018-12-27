#include "meta_data_list.h"

using namespace oak;

MetaData* MetaDataList::findMetaData(const std::string& selector)
{
  for (auto it = list.begin(); it != list.end(); it++)
  {
    if (it->selector == selector)
    {
      return &(*it);
    }

  }
  return nullptr;
}

const Var* MetaDataList::getVar(const std::string& selector, const std::string& key)
{
  MetaData* md = findMetaData(selector);
  if (md != nullptr)
  {
    return md->getKV(key);
  }

  return &MetaData::VAR_NULL;
}

void MetaDataList::add(MetaData* md)
{
  if (md != nullptr)
  {
    if (md->selector.size() == 0)
    {
      delete md;
    }
    else
    {
      list.push_back(*md);
    }
  }
}

std::vector<MetaData>& MetaDataList::getList()
{
  return list;
}