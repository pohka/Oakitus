#include "style_loader.h"
#include "style.h"
#include <iostream>
#include <fstream>
#include <oak/debug.h>
#include <oak/core/string_help.h>
#include <unordered_map>
#include <oak/ui/ui_canvas.h>

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

  LOG << "----- RELOADING STYLE -------";
  //reload css files
  for (auto it = loadedFiles.begin(); it != loadedFiles.end(); it++)
  {
    parse(*it);
  }
  LOG << "-------------";
  
  //recompute styles
  for (auto it = UICanvas::components.begin(); it != UICanvas::components.end(); it++)
  {
    it->second->recomputeStyle();
  }
}


 
void StyleLoader::parse(std::string path)
{
  string line;
  ifstream file(path);

  char ch;
  uchar state = STATE_CLASSNAME;
  string text, key, val;
  uint lineNum = 1;
  vector<string> selectors;
  unordered_map<string, string> attrs;

  //i fucked this up
  if (file.is_open())
  {
    while (file.get(ch))
    {
      if (ch == '\n')
      {
        lineNum++;
        if (state >= STATE_ATTR_KEY)
        {
          if (text.size() > 0)
          {
            LOG << "---CSS PARSING ERROR---| '" << path << "' line:" << lineNum << " | missing ';' at end of line";
          }
          state = STATE_ATTR_KEY;
          text.clear();
        }
      }
      else if (
        (state < STATE_ATTR_VALUE && ch != ' ' && ch != '\t') ||
        (state == STATE_ATTR_VALUE && ch != '\t'))
      {
        if (ch == '{')
        {
          if (state != STATE_CLASSNAME)
          {
            LOG << "---CSS PARSING ERROR---| '" << path << "' line:" << lineNum << " | invalid location for '{'";
          }
          else
          {
            bool success = parseSelectors(text, selectors);
            if (!success)
            {
              LOG << "---CSS PARSING ERROR---| near line:" << lineNum << " | no style class name was found";
            }
            state = STATE_ATTR_KEY;
            text.clear();
          }
        }
        else if (ch == '}')
        {
          if (state != STATE_ATTR_KEY)
          {
            LOG << "---CSS PARSING ERROR---| line:" << lineNum << " | invalid location for '}'";
          }
          else
          {
            state = STATE_CLASSNAME;
            for (uint i = 0; i < selectors.size(); i++)
            {
              Style* style = new Style(selectors[i], attrs);
              UICanvas::addStyle(style);
            }
          }
          text.clear();
        }
        //end of key
        else if (ch == ':' && state >= STATE_ATTR_KEY)
        {
          if (state == STATE_ATTR_KEY)
          {
            state = STATE_ATTR_VALUE;
            key = text;
            text.clear();
          }
          else
          {
            LOG << "---CSS PARSING ERROR---| line:" << lineNum << " | invalid location for ':'";
          }
        }
        //end of kv
        else if (ch == ';')
        {
          //if no value
          if (state != STATE_ATTR_VALUE)
          {
            LOG << "---CSS PARSING ERROR---| line:" << lineNum << " | unknown symbol ';'";
          }
          //has a value and a key
          else
          {
            val = text;
            //remove trailing space for value
            if (val.size() > 0 && val.back() == ' ')
            {
              val.pop_back();
            }
            attrs.insert_or_assign(key, val);
          }
          //reset to key
          state = STATE_ATTR_KEY;
          key.clear();
          val.clear();
          text.clear();
        }
        else if (ch == ' ')
        {
          //don't capture multiple spaces
          if (text.size() > 0 && text.back() != ' ')
          {
            text += ch;
          }
        }
        else
        {
          text += ch;
        }
      }
    }
  }
}

bool StyleLoader::parseSelectors(string& text, vector<string>& strs)
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
