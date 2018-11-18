#include "xml_parser.h"

#include <iostream>
#include <fstream>
#include "../core/resources.h"

using namespace std;

static void printNodes(XMLNode* node, unsigned int depth)
{
  std::cout << "node (" << depth << "):" << node->name << ":" << node->content << ";" << std::endl;
  for (unsigned int i = 0; i < node->getChildNodes().size(); i++)
  {
    printNodes(node->getChildNodes()[i], depth+1);
  }
}

XMLNode XMLParser::load(string file)
{
  string line;
  ifstream myfile(oak::Resources::PATH + file);

  XMLNode* root = new XMLNode("root", nullptr);

  XMLNode* curNode = root;
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
              XMLNode* node = new XMLNode(tagName, curNode);
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

    //XMLNode* map = root->getChildNodes()[0];

   //std::cout << "--------" << std::endl;
    //printNodes(map, 0);

    //std::cout << "xml:" << map->getName() << ":" << map->getContent() << ";" << std::endl;
    //std::cout << map->getChildNodes()[0]->getName() << ":" << map->getChildNodes()[0]->getContent() << ";" << std::endl;

    // XMLNode* root2 = new XMLNode("map");
     //XMLNode* ch = new XMLNode("test");
     //ch->setContent("123");
    // root2->appendChild(ch);

    return *root;
  }
}

