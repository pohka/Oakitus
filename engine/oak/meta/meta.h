#ifndef META_LOADER_H
#define META_LOADER_H

#include <unordered_map>
#include "meta_data_list.h"

namespace oak
{
  struct Meta
  {
    //load the config file and all the meta data for the current project
    static void load();

    //once load, this list contains all the meta data loaded for this project
    static MetaDataList globalMetaList;

    //get a value from the config by key
    static std::string getConfigVal(const std::string& key);

  private:
    //parses the all the files contents i.e. <fileName, contents>
    static void parseFiles(std::unordered_map<std::string, std::string>& files);

    //parse the content and output to out
    static void parseContent(const std::string& fileName, std::string& content, MetaDataList& out);

    //load the config.m file
    static void loadConfig();

    //config meta data
    static MetaData config;
    
    //states when parsing meta data files
    static const char STATE_BEFORE_SELECTOR = 0;
    static const char STATE_SELECTOR = 1;
    static const char STATE_BEFORE_KEY = 3;
    static const char STATE_KEY = 4;
    static const char STATE_BEFORE_VAL = 5;
    static const char STATE_VAL = 6;
  };
}

#endif