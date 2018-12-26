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

    std::string get(const std::string& key)
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

    void copy(MetaData& rhs)
    {
      rhs.selector = selector;
      rhs.kvs.clear();
      for (unsigned int i = 0; i < kvs.size(); i++)
      {
        rhs.kvs.push_back({ kvs[i].key, kvs[i].val });
      }
    }
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

    std::string get(const std::string& selector, const std::string& key)
    {
      MetaData* md = find(selector);
      if (md != nullptr)
      {
        return md->get(key);
      }

      return "";
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
    static MetaDataList globalMetaList;

  private:
    static void parseFiles(std::unordered_map<std::string, std::string>& files);
    static void parseContent(const std::string& fileName, std::string& content, MetaDataList& out);
    static void loadConfig();

    static MetaData config;
    

    static const char STATE_BEFORE_SELECTOR = 0;
    static const char STATE_SELECTOR = 1;
    static const char STATE_BEFORE_KEY = 3;
    static const char STATE_KEY = 4;
    static const char STATE_BEFORE_VAL = 5;
    static const char STATE_VAL = 6;
  };
}

#endif