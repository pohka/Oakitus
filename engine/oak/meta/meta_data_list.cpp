#include "meta_data_list.h"

using namespace oak;

MetaData* MetaDataList::find(const std::string& selector)
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

std::string MetaDataList::get(const std::string& selector, const std::string& key)
{
  MetaData* md = find(selector);
  if (md != nullptr)
  {
    return md->get(key);
  }

  return "";
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