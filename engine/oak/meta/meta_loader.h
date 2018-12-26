#ifndef META_LOADER_H
#define META_LOADER_H

#include <unordered_map>
#include <vector>
#include <string>

namespace oak
{
  struct MetaKV
  {
    std::string key;
    std::string val;
  };

  struct MetaData
  {
    std::string selector;
    std::vector<MetaKV> kvs;
  };

  struct MetaDataList
  {
    MetaData* find(const std::string& selector)
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

    void add(MetaData* md)
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

    std::vector<MetaData>& getList()
    {
      return list;
    }

    private:
      std::vector<MetaData> list;
  };

  struct MetaLoader
  {
    static void load();
    static MetaDataList metaDataList;

  private:
    static void parseFiles(std::unordered_map<std::string, std::string>& files);
    static void parseContent(const std::string& fileName, std::string& content);
    

    static const char STATE_BEFORE_SELECTOR = 0;
    static const char STATE_SELECTOR = 1;
    static const char STATE_BEFORE_KEY = 3;
    static const char STATE_KEY = 4;
    static const char STATE_BEFORE_VAL = 5;
    static const char STATE_VAL = 6;
  };
}

#endif