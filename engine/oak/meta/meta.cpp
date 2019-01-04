#include "meta.h"
#include <oak/build_def.h>
#ifdef DEBUG_MODE
  #include <iostream>
#endif
#include <fstream>
#include <cctype>
#include "var.h"

#include <oak/build_def.h>
#ifdef PLATFORM_WINDOWS
  #include <windows.h>
#endif

using namespace oak;

kvmap<std::string, var_object*> Meta::objs;


void Meta::load(const char* filepath)
{
  //get full path to file
  std::string root = dir();
  std::string path = root + "\\..\\" + filepath;

  //read file
  std::ifstream ifs(path);

  //output to content string
  std::string content(
    (std::istreambuf_iterator<char>(ifs)),
    (std::istreambuf_iterator<char>())
  );

  //parse
  unsigned int i = 0;
  parse(content, i);
}

//returns the directory (NOTE: windows only)
std::string Meta::dir() 
{
  #ifdef PLATFORM_WINDOWS
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
  #else
    #error Target platform not set
    return "";
  #endif
}

//how parsing works
//-----------------
//iterates through each character
//certain characters can change the state
//the char is handled seperatly by each state, except for '\n'
void Meta::parse(std::string& content, unsigned int& index)
{
  bool isSpace;
  unsigned char state = STATE_BEFORE_OBJ;
  unsigned char varType = VAR_NULL;
  std::string key = "", val= "";
  int lineNum = 1;

  var_object* obj = nullptr;
  char ch;
  while (index<content.size())
  {
    ch = content[index];
    isSpace = std::isspace(ch);

    //new line
    if (ch == '\n')
    {
      if (state > STATE_AFTER_OBJ)
      {
        //check if there was a parsing error in the key value states
        if (state < STATE_VAL)
        {
          if (key.size() > 0)
          {
#ifdef DEBUG_MODE
            std::cout << "--PARSRING ERROR--| line:" << lineNum << " state:" << std::to_string(state) << std::endl;
#endif
          }
        }
        else
        {
          //successfully parsed, add var to object
          if (val.size() > 0 || (val.size() == 0 && varType == VAR_STRING))
          {
            var* v = new var(val, varType);
            obj->kvs.add(key, v);
          }
          else
          {
#ifdef DEBUG_MODE
            std::cout << "--PARSRING ERROR--| line:" << lineNum << " val is empty" << std::endl;
#endif
          }
        }

        //reset parsing variables
        varType = VAR_NULL;
        key.clear();
        val.clear();
        state = STATE_BEFORE_KEY;
      }
      lineNum++;
    }

    //handle char based on the state
    switch (state)
    {
      case STATE_BEFORE_OBJ :
        if (!isSpace)
        {
          state = STATE_OBJ;
          key = ch;
        }
        break;
      case STATE_OBJ :
        if (isSpace || ch == ':')
        {
          state = STATE_AFTER_OBJ;
        }
        else
        {
          key += ch;
        }
        break;
      case STATE_AFTER_OBJ :
        if (ch == '{')
        {
          obj = new var_object();
          objs.add(key, obj);
          key.clear();
          varType = VAR_NULL;
          state = STATE_BEFORE_KEY;
        }
        break;
      case STATE_BEFORE_KEY :
        if (!isSpace)
        {
          if (ch == '}')
          {
            state = STATE_BEFORE_OBJ;
          }
          else
          {
            state = STATE_KEY;
            key += ch;
          }
        }
        break;
      case STATE_KEY :
        if (isSpace)
        {
          state = STATE_AFTER_KEY;
        }
        else if (ch == ':')
        {
          state = STATE_BEFORE_VAL;
        }
        else
        {
          key += ch;
        }
        break;
      case STATE_AFTER_KEY :
        if (ch == ':')
        {
          state = STATE_BEFORE_VAL;
        }
        break;
      case STATE_BEFORE_VAL :
        if (!isSpace)
        {
          state = STATE_VAL;

          if (ch == '"')
          {
            varType = VAR_STRING;
          }
          else if (ch <= '9' && ch >= '0')
          {
            varType = VAR_NUMBER;
            val += ch;
          }
          else if (ch == 't' || ch == 'f' || ch == 'T' || ch == 'F')
          {
            varType = VAR_BOOL;
            val += ch;
          }
          else if (ch == '{')
          {
            varType = VAR_OBJECT;
          }
        }
        break;
      case STATE_VAL :
        if (varType == VAR_STRING)
        {
          if (ch == '"')
          {
            state = STATE_AFTER_VAL;
          }
          else
          {
            val += ch;
          }
        }
        else if (varType == VAR_NUMBER)
        {
          if ((ch <= '9' && ch >= '0') || ch == '.')
          {
            val += ch;
          }
          else
          {
            state = STATE_AFTER_VAL;
          }
        }
        else if (varType == VAR_BOOL && isSpace)
        {
          state = STATE_AFTER_VAL;
        }
        break;
    }

    index++;
  }
}

