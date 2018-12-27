#include "meta.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cctype>
#include <oak/core/resources.h>

using namespace oak;

MetaDataList Meta::globalMetaList;
MetaData Meta::config;

void Meta::loadConfig()
{
  //parse config.m
  std::ifstream ifs("../config.m");
  std::string content(
    (std::istreambuf_iterator<char>(ifs)),
    (std::istreambuf_iterator<char>())
  );
  MetaDataList list;
  parseContent("config.m", content, list);
  list.findMetaData("config")->copy(config);
}

void Meta::load()
{
  loadConfig();

  std::cout << "----META----" << std::endl;

  std::string fullPath, path;

  std::string projectName = VarString::get(config.findVar("project"));
  //float damage = VarNumber::get(config.findVar("damage"));
  //std::cout << "damage from copy:" << damage << std::endl;



  if (projectName.size() == 0)
  {
    std::cout << "CONFIG ERROR" << std::endl;
    return;
  }

  Resources::rootPath = "../projects/" + projectName + "/resources/";

  std::string root = std::filesystem::current_path().parent_path().generic_string() + "/projects/" + projectName + "/";
  std::cout << "root path: " << root << std::endl;

  std::unordered_map<std::string, std::string> files;

  for (const auto & entry : std::filesystem::recursive_directory_iterator(root))
  {

    if (".m" == entry.path().extension())
    {
      std::cout << "found:" << entry.path().filename() << std::endl;
      fullPath = entry.path().generic_string();

      path = fullPath.substr(root.size());

      std::cout << "path:" << path << std::endl;

      std::ifstream ifs(root + path);
      std::string content(
        (std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
      );

      files.insert_or_assign(path, content);
    }
  }

  std::cout << "------------" << std::endl;

  parseFiles(files);

  //std::cout << std::endl << "results:" << std::endl;
  //std::vector<MetaData>& list = globalMetaList.getList();
  //for (unsigned int i = 0; i < list.size(); i++)
  //{
  //  std::cout << "selector:" << list[i].selector << std::endl;
  //  for (MetaKV kv : list[i].kvs)
  //  {
  //    std::cout << kv.key << ":" << kv.val << std::endl;
  //  }
  //  std::cout << "==========" << std::endl;
  //}

}

void Meta::parseFiles(std::unordered_map<std::string, std::string>& files)
{
  for (auto it = files.begin(); it != files.end(); it++)
  {
    parseContent(it->first, it->second, globalMetaList);
  }
}


void Meta::parseContent(const std::string& fileName, std::string& content, MetaDataList& out)
{
  //std::cout << "content: " << std::endl << content << std::endl;

  MetaData* metaData = nullptr;
  char state = STATE_BEFORE_SELECTOR;

  bool isSpace = false;
  std::string key, val;
  unsigned int lineNum = 1;

  unsigned char varType = VAR_TYPE_STRING;

  for (char& ch : content) 
  {
    if (ch == '\n')
    {
      if (state == STATE_BEFORE_KEY && key.size() && key.size() > 0)
      {
        if (varType == VAR_TYPE_STRING)
        {
          Var* var = new VarString(val);
          metaData->addKV(new MetaKV(key, var));
        }
        else if(varType == VAR_TYPE_NUMBER)
        {
          float num = std::stof(val);
          Var* var = new VarNumber(num);
          metaData->addKV(new MetaKV(key, var));
        }
      }
      else if (state == STATE_VAL && varType == VAR_TYPE_NUMBER && val.size() > 0)
      {
        float num = std::stof(val);
        Var* var = new VarNumber(num);
        metaData->addKV(new MetaKV(key, var));
      }
      else if (state > STATE_BEFORE_KEY)
      {
        if (
          !(state == STATE_VAL && varType == VAR_TYPE_NUMBER && val.size() > 0)
          )
        {
          std::cout << "'" << fileName << "' parsing error line:" << lineNum << std::endl;
        }
        state = STATE_BEFORE_KEY;
      }

      key.clear();
      val.clear();

      lineNum++;
    }

    isSpace = isspace(ch);

    if (state == STATE_BEFORE_SELECTOR)
    {
      if (!isSpace)
      {
        state = STATE_SELECTOR;
        metaData = new MetaData();
        metaData->selector = ch;
      }
    }
    else if (state == STATE_SELECTOR)
    {
      if (!isSpace)
      {
        if (ch == '{')
        {
          if (metaData->selector.size() == 0)
          {
            std::cout << "'" << fileName << "' parsing error line:" << lineNum << "| selector has no name" << std::endl;
          }
          state = STATE_BEFORE_KEY;
          key = "";
        }
        else
        {
          metaData->selector += ch;
        }
      }
    }
    else if (state == STATE_BEFORE_KEY)
    {
      if (ch == '}')
      {
        out.add(metaData);
        state = STATE_BEFORE_SELECTOR;
      }
      else if (!isSpace)
      {
        key = ch;
        state = STATE_KEY;
      }
    }
    else if (state == STATE_KEY)
    {
      if (ch == ':')
      {
        state = STATE_BEFORE_VAL;
      }
      else if (!isSpace)
      {
        key += ch;
      }
    }
    else if (state == STATE_BEFORE_VAL)
    {
      if (!isSpace)
      {
        state = STATE_VAL;
        val = "";

        if (ch == '"')
        {
          varType = VAR_TYPE_STRING;
        }
        else if(ch <= '9' && ch >= '0')
        {
          varType = VAR_TYPE_NUMBER;
          val += ch;
        }
      }
    }
    else if (state == STATE_VAL)
    {
      //if value ended
      if (
        (ch == '"' && varType == VAR_TYPE_STRING) ||
        (isSpace && varType == VAR_TYPE_NUMBER)
        )
      {
        state = STATE_BEFORE_KEY;
      }
      else
      {
        if (varType == VAR_TYPE_STRING)
        {
          val += ch;
        }
        else if (varType == VAR_TYPE_NUMBER)
        {
          val += ch;
        }
      }
    }
  }
}

std::string Meta::getConfigVal(const std::string& key)
{
  return "";// todo: config.getKV(key);
}