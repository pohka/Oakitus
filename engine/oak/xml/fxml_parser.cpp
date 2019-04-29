#include "fxml_parser.h"

#include <oak/build_def.h>
#ifdef DEBUG_MODE
  #include <iostream>
#endif
#include <fstream>
#include <oak/core/resources.h>
#include <oak/oak_def.h>

using namespace std;
using namespace oak;

//used for debugging
static void printNodes(FXMLNode* node, unsigned int depth)
{
#ifdef DEBUG_MODE
  std::cout << "node (" << depth << "):" << node->name << ":" << node->content << ";" << std::endl;
  for (unsigned int i = 0; i < node->getChildNodes().size(); i++)
  {
    printNodes(node->getChildNodes()[i], depth+1);
  }
#endif
}

//fast XML parser
//this implementation doesn't parse attributes or comments and only allows leaf nodes to have content
FXMLNode FXMLParser::load(string file)
{
  string line;
  ifstream myfile(Resources::ENGINE_RESOURCES_ROOT_PATH + file);

  FXMLNode* root = new FXMLNode("root", nullptr);

  FXMLNode* curNode = root;
  string content = "";
  string tagName;

  if (myfile.is_open())
  {
    bool isTagOpen = false;

    while (getline(myfile, line))
    {
      //std::cout << line << std::endl;
      for (char& c : line) 
      {
        if (isTagOpen)
        {
          //end of tag
          if (c == '>')
          {
            isTagOpen = false;

            //is opening tag
            if (tagName.front() != '/')
            {
              FXMLNode* node = new FXMLNode(tagName, curNode);
              curNode->appendChild(node);
              curNode = node;
            }
            //is closing tag
            else
            {
              tagName = "";
              curNode = curNode->getParent();
            }
          }
          else
          {
            tagName += c;
          }
        }
        //start of a tag
        else if (c == '<')
        {
          isTagOpen = true;
          tagName = "";
        }
        else
        {
          bool isSpace = isspace(c);
          if (!isSpace || (isSpace && !curNode->content.empty()))
          {
            curNode->content += c;
          }
        }
      }
        
      
    }
    myfile.close();

    return *root;
  }

  return *new FXMLNode("", nullptr);
}

