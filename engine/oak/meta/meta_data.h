#ifndef META_DATA_H
#define META_DATA_H

#include <string>
#include <vector>

namespace oak
{
  struct MetaKV
  {
    const std::string key;
    std::string val;
  };

  struct MetaData
  {
    std::string selector;
    std::vector<MetaKV> kvs;

    //get value by key, if not found then an empty string is returned
    std::string get(const std::string& key);

    //makes a deep copy and outputs to rhs
    void copy(MetaData& rhs);
  };
}

#endif