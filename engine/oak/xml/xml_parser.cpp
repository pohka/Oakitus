#include "xml_parser.h"
#include <fstream>
#include <iostream>

using namespace oak;

XMLParser::XMLParser() {}

XMLParser::~XMLParser()
{
  clear();
}

XMLNode* XMLParser::getRootNode() const
{
  return root;
}

void XMLParser::clear()
{
  if (root != nullptr)
  {
    delete root;
  }
}

std::string XMLParser::nodeToString(const XMLNode& node, unsigned int depth) const
{
  std::string str = "";
  //indenting
  for (unsigned int i = 0; i < depth; i++)
  {
    str += '  ';
  }

  str += "<" + node.tag;
  for (auto it : node.attrs)
  {
    str += " " + it.first + "=\"" + it.second + "\"";
  }
  str += ">" + node.text;

  if (node.children.size() > 0)
  {
    str += "\n";
  }
  for (auto it : node.children)
  {
    str += XMLParser::nodeToString(*it, depth + 1);
  }
  //indent for ending tag
  if (node.children.size() > 0)
  {
    for (unsigned int i = 0; i < depth; i++)
    {
      str += '  ';
    }
  }

  str += "</" + node.tag + ">\n";

  return str;
}

void XMLParser::trimText(XMLNode* node)
{
  bool prevIsSpace = true;
  bool isSpace = false;

  unsigned int i = 0;
  while (i < node->text.size())
  {
    isSpace = isspace(node->text[i]);
    if ((prevIsSpace && isSpace) || node->text[i] == '\n')
    {
      node->text.erase(node->text.begin() + i);
      prevIsSpace = true;
    }
    else
    {
      prevIsSpace = isSpace;
      i++;
    }
  }

  //last character cannot be a space
  if (!node->text.empty() && isspace(node->text.back()))
  {
    node->text.pop_back();
  }
}

bool XMLParser::load(const std::string& path)
{
  std::ifstream ifs(path);

  bool isAttrValueOpen = false; //is true if in quotes of attribute value

  if (ifs.is_open())
  {
    char ch;
    char prevCh = 0;
    std::string key = "";
    std::string value = "";
    std::string buffer = "";
    
    const std::string commentClose = "-->";
    const unsigned int MAX_BUFFER_SIZE = 3;
    bool isInComment = false;

    XMLNode* node = nullptr;
    char state = STATE_NONE;
    char tokenID = TOKEN_NONE;
    errorCode = ERROR_NONE;

    while (ifs.get(ch) && errorCode == 0)
    {
      //store recent characters
      buffer += ch;
      if (buffer.size() > MAX_BUFFER_SIZE)
      {
        buffer.erase(buffer.begin());
      }

      tokenID = getTokenID(ch, prevCh);

      //ecsape comment
      if (isInComment)
      {
        if (buffer == commentClose)
        {
          isInComment = false;
        }
      }
      else
      {
        switch (state)
        {
        case STATE_NONE:
        {
          //opening root tag
          if (root == nullptr && tokenID == TOKEN_TAG_BEGIN)
          {
            state = STATE_OPEN_TAG_BEGIN;
            node = new XMLNode();
            node->parent = nullptr;
            root = node;
          }
          //PARSING ERROR: file did not begin with an opening tag
          else if (root == nullptr && !(tokenID == TOKEN_NONE | TOKEN_TAG_BEGIN))
          {
            errorCode = ERROR_PARSING_ROOT_TAG;
            break;
          }
        }
        break;
        case STATE_OPEN_TAG_BEGIN:
        {
          //end of opening tag with no attrs
          if (tokenID == TOKEN_TAG_END)
          {
            state = STATE_CONTENT;
          }
          else if (isspace(ch))
          {
            state = STATE_ATTRS;
          }
          else
          {
            //PARSING ERROR: invalid character found in tag name
            if (tokenID != TOKEN_NONE)
            {
              errorCode = ERROR_PARSING_TAG_NAME;
              break;
            }
            node->tag += ch;
          }
        }
        break;
        case STATE_ATTRS:
        {
          //end of opening tag with attrs
          if (tokenID == TOKEN_TAG_END)
          {
            state = STATE_CONTENT;
            key.clear();
            value.clear();
          }
          else
          {
            //PARSING ERROR: attribute key starts with an invalid character
            if (tokenID != TOKEN_NONE)
            {
              errorCode = ERROR_PARSING_KEY;
              break;
            }
            else if (!isspace(ch))
            {
              key += ch;
              state = STATE_ATTR_KEY;
            }
          }
        }
        break;
        case STATE_ATTR_KEY:
        {
          if (tokenID == TOKEN_EQUALS)
          {
            state = STATE_ATTR_VALUE;
          }
          else
          {
            //PARSING ERROR: invalid character, when a key name was expetected
            if (!(tokenID == TOKEN_NONE) || isspace(ch))
            {
              errorCode = ERROR_PARSING_KEY;
              break;
            }
            key += ch;
          }
        }
        break;
        case STATE_ATTR_VALUE:
        {
          if (tokenID == TOKEN_QUOTE && !isAttrValueOpen)
          {
            isAttrValueOpen = true;
          }
          //end of attr
          else if (isAttrValueOpen && tokenID == TOKEN_QUOTE)
          {
            node->attrs[key] = value;
            value.clear();
            key.clear();
            state = STATE_ATTRS;
            isAttrValueOpen = false;
          }
          else if (isAttrValueOpen)
          {
            value += ch;
          }
          //no value
          else if (!isAttrValueOpen && isspace(ch))
          {
            if (!key.empty())
            {
              node->attrs[key] = "";
            }
            state = STATE_ATTRS;
          }
        }
        break;
        case STATE_CONTENT:
        {
          //start of child tag or start of closing tag
          if (tokenID == TOKEN_TAG_BEGIN)
          {
            trimText(node);
            state = STATE_NEXT_TAG;
          }
          else
          {
            //PARSING ERROR: unexpected character in textContent
            if (!(tokenID == TOKEN_NONE | TOKEN_TAG_BEGIN))
            {
              errorCode = ERROR_PARSING_TEXT;
              break;
            }
            node->text += ch;
          }
        }
        break;
        case STATE_NEXT_TAG:
        {
          //is closing tag
          if (tokenID == TOKEN_TAG_BEGIN_CLOSING)
          {
            state = STATE_CLOSING_TAG;
          }
          //child tag
          else if (tokenID == TOKEN_NONE)
          {
            if (isspace(ch))
            {
              errorCode = ERROR_PARSING_TAG_NAME;
              break;
            }
            else if (ch == '!')
            {
              isInComment = true;
              state = STATE_CONTENT;
            }
            else
            {
              //first character should be the tag name
              state = STATE_OPEN_TAG_BEGIN;
              XMLNode* parent = node;
              node = new XMLNode();
              node->parent = parent;
              parent->children.push_back(node);
              node->tag += ch;
            }
          }
          //PARSING ERROR: unxpected characater at the start of the tag
          else
          {
            errorCode = ERROR_PARSING_TAG_NAME;
            break;
          }
        }
        break;
        case STATE_CLOSING_TAG:
        {
          //end of closing tag
          if (tokenID == TOKEN_TAG_END)
          {
            //trimText(node);
            node = node->parent;
            if (node == nullptr)
            {
              state = STATE_NONE;
            }
            else
            {
              state = STATE_CONTENT;
            }
          }
          //PARSING ERROR:  unexpected character in closing tag
          else if (tokenID != TOKEN_NONE)
          {
            errorCode = 6;
            break;
          }
          //else ignore characters
        }
        break;
        }
      }
    
      prevCh = ch;
    }

    ifs.close();
    std::cout << nodeToString(*root) << std::endl;
  }
  //failed to load file
  else
  {
  errorCode = ERROR_FILE_OPEN;
    return false;
  }
  
  return errorCode == ERROR_NONE;
}

char XMLParser::getTokenID(char ch, char prevCh) const
{
  for (unsigned int i = 0; i < TOKEN_COUNT; i++)
  {
    if (
      (tokens[i].prevCh == NULL && tokens[i].ch == ch && prevCh != '\\') ||
      (tokens[i].prevCh != NULL && tokens[i].prevCh == prevCh && tokens[i].ch == ch)
     )
    {
      return tokens[i].id;
    }
  }
  return TOKEN_NONE;
}

char XMLParser::getErrorCode() const
{
  return errorCode;
}

bool XMLParser::save(const std::string& path)
{
  std::ofstream ofs(path);
  if (ofs.is_open())
  {
    ofs << nodeToString(*root);
    ofs.close();
  }
  else
  {
    return false;
  }
  return true;
}