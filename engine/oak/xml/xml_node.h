#ifndef XML_NODE_H
#define XML_NODE_H

#include <string>
#include <vector>
#include <map>

namespace oak
{
  class XMLNode
  {
    XMLNode* parent;
    std::string tag;
    std::string text = "";
    std::map<const std::string, std::string> attrs = {};
    std::vector<XMLNode*> children;

  public:
    friend class XMLParser;
    XMLNode();
    ~XMLNode();
  };
}

#endif