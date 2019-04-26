#ifndef FXML_NODE_H
#define FXML_NODE_H

#include <string>
#include <vector>

namespace oak
{
  //An fast XML node
  class FXMLNode
  {
    std::vector<FXMLNode*> children; //all the child nodes
    FXMLNode* parent; //parent node

  public:
    std::string content; //content between the opening and closing tags
    std::string name; //name of the tag

    FXMLNode(std::string name, FXMLNode* parent);
    ~FXMLNode();
    void appendChild(FXMLNode* node);
    std::vector<FXMLNode*> getChildNodes() const;
    FXMLNode* getParent() const;
    bool hasChildNodes() const;
  };
}

#endif