#ifndef XML_NODE_H
#define XML_NODE_H

#include <string>
#include <vector>

///<summary>An XML node</summary>
class XMLNode
{
  
  std::vector<XMLNode*> children; //all the child nodes
  XMLNode* parent; //parent node

  public :
    std::string content; //content between the opening and closing tags
    std::string name; //name of the tag

    XMLNode(std::string name, XMLNode* parent);
    ~XMLNode();
    void appendChild(XMLNode* node);
    std::vector<XMLNode*> getChildNodes() const;
    XMLNode* getParent() const;
    bool hasChildNodes() const;
};

#endif