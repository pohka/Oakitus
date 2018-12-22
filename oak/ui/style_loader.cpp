#include "style_loader.h"
#include "style.h"
#include <iostream>
#include <fstream>
#include <debug.h>
#include <core/string_help.h>
#include <unordered_map>
#include <ui/ui_canvas.h>

using namespace ion;
using namespace std;

vector<string> StyleLoader::loadedFiles;

void StyleLoader::load(string path)
{
  loadedFiles.push_back(path);
  parse(path);
}

void StyleLoader::reload()
{
  //delete existing styles
  UICanvas::deleteAllStyles();

  //reload css files
  for (auto it = loadedFiles.begin(); it != loadedFiles.end(); it++)
  {
    parse(*it);
  }
  
  //recompute styles
  for (auto it = UICanvas::components.begin(); it != UICanvas::components.end(); it++)
  {
    it->second->recalcStyle();
  }
}


 
void StyleLoader::parse(std::string path)
{
  cout << "----- LOADING STYLE -------" << endl;
  string line;
  ifstream file(path);

  char ch;
  uchar state = STATE_CLASSNAME;
  string text;
  uint lineCount = 0;
  vector<string> classList;
  unordered_map<string, string> attrs;
  pair<string, string> kv;

  

  if (file.is_open())
  {
    while (file.get(ch))
    {
      if (ch == '\n')
      {
        lineCount++;
        if (state == STATE_ATTRIBUTES)
        {
          /*if (text.size() > 0)
          {

          }*/
        }
      }
      else if (ch != ' ' && ch != '\t')
      {
        if (ch == '{')
        {
          if (state != STATE_CLASSNAME)
          {
            LOG_WARNING << "---CSS PARSING ERROR---| line:" << lineCount << " , invalid location for '{'";
          }
          else
          {
            state = STATE_ATTRIBUTES;
            bool success = parseClassNames(text, classList);
            if (!success)
            {
              LOG_WARNING << "---CSS PARSING ERROR---| near line:" << lineCount << "no style class name was found";
            }
            text.clear();
          }
        }
        else if (ch == '}')
        {
          if (state != STATE_ATTRIBUTES)
          {
            LOG_WARNING << "---CSS PARSING ERROR---| line:" << lineCount << " , invalid location for '}'";
          }
          else
          {
            state = STATE_CLASSNAME;
            Style* style = new Style(classList, attrs);
            UICanvas::addStyle(style);
            text.clear();
          }
        }
        else if (ch == ';')
        {
          if (state != STATE_ATTRIBUTES)
          {
            LOG_WARNING << "---CSS PARSING ERROR---| line:" << lineCount << " , unknown symbol ';'";
          }
          else
          {
            bool success = parseAttr(text, kv, lineCount);
            if (success)
            {
              attrs.insert_or_assign(kv.first, kv.second);
            }
          }
        }
        else
        {
          text += ch;
        }
      }
    }
  }

  cout << "-------------" << endl;
}

bool StyleLoader::parseClassNames(string& text, vector<string>& strs)
{
  oak::StringHelp::split(text, strs, ',');
  if (strs.size() == 0)
  {
    return false;
  }

  for (uint i = 0; i < strs.size(); i++)
  {
    if (strs[i][0] == '.' || strs[i][0] == '#')
    {
      strs[i] = strs[i].substr(1);
    }
  }

  
  return true;
}

bool StyleLoader::parseAttr(
  string& line, 
  pair<string, string>& kv, 
  unsigned int lineNum
)
{
  string key = "";
  string val = "";
  for (uint i=0; i<line.size(); i++)
  {
    if (line[i] == ':')
    {
      key = line.substr(0, i);
      if (i + 1 < line.size())
      {
        val = line.substr(i + 1);
      }
      break;
    }
  }

  if (key.size() == 0 || val.size() == 0)
  {
    LOG_WARNING << "---CSS PARSING ERROR---| line:" << lineNum << " , invalid attribute";
    return false;
  }

  kv.first = key;
  kv.second = val;
  return true;
}