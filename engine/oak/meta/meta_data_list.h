#ifndef META_DATA_LIST_H
#define META_DATA_LIST_H

#include "meta_data.h"

namespace oak
{
  struct MetaDataList
  {
    //find the meta data by selector, if not found returns a nullptr
    MetaData* find(const std::string& selector);

    //find the value by selector and key, if not found an empty string is returned
    std::string get(const std::string& selector, const std::string& key);

    //add meta data to the list
    void add(MetaData* md);

    //return the entire list
    std::vector<MetaData>& getList();

  private:
    std::vector<MetaData> list;
  };
}

#endif