#include "style_loader.h"
#include "style.h"
#include <fstream>

#include <oak/build_def.h>
#ifdef DEBUG_MODE
#include <oak/debug.h>
#endif

#include <oak/core/string_help.h>
#include <unordered_map>
#include <oak/ui/ui_canvas.h>

using namespace ion;
using namespace std;

vector<string> StyleLoader::loadedFiles;

void StyleLoader::load(const string& path)
{
  loadedFiles.push_back(path);
  parse(path);
}

void StyleLoader::reload()
{
  //delete existing styles
  UICanvas::deleteAllStyles();

#ifdef DEBUG_MODE
  LOG << "----- RELOADING STYLE -------";
  //reload css files
  for (auto it = loadedFiles.begin(); it != loadedFiles.end(); it++)
  {
    parse(*it);
  }
  LOG << "-------------";
#endif
  
  //recompute styles
  for (auto it = UICanvas::widgets.begin(); it != UICanvas::widgets.end(); it++)
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
#ifdef DEBUG_MODE
            LOG << "---CSS PARSING ERROR---| '" << path << "' line:" << lineNum << " | missing ';' at end of line";
#endif
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
#ifdef DEBUG_MODE
            LOG << "---CSS PARSING ERROR---| '" << path << "' line:" << lineNum << " | invalid location for '{'";
#endif
          }
          else
          {
            bool success = parseSelectors(text, selectors);
            if (!success)
            {
#ifdef DEBUG_MODE
              LOG << "---CSS PARSING ERROR---| near line:" << lineNum << " | no style class name was found";
#endif
            }
            state = STATE_ATTR_KEY;
            text.clear();
          }
        }
        else if (ch == '}')
        {
          if (state != STATE_ATTR_KEY)
          {
#ifdef DEBUG_MODE
            LOG << "---CSS PARSING ERROR---| line:" << lineNum << " | invalid location for '}'";
#endif
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
#ifdef DEBUG_MODE
            LOG << "---CSS PARSING ERROR---| line:" << lineNum << " | invalid location for ':'";
#endif
          }
        }
        //end of kv
        else if (ch == ';')
        {
          //if no value
          if (state != STATE_ATTR_VALUE)
          {
#ifdef DEBUG_MODE
            LOG << "---CSS PARSING ERROR---| line:" << lineNum << " | unknown symbol ';'";
#endif
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
