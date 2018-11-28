#ifndef XML_NODE_H
#define XML_NODE_H

#include <string>
#include <vector>

class XMLNode
{
  
  std::vector<XMLNode*> children;
  XMLNode* parent;

  public :
    std::string content;
    std::string name;

    XMLNode(std::string name, XMLNode* parent);
    ~XMLNode();
    void appendChild(XMLNode* node);
    std::vector<XMLNode*> getChildNodes() const;
    XMLNode* getParent() const;
    bool hasChildNodes() const;
};

#endif