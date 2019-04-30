#include "fxml_node.h"

using namespace oak;

FXMLNode::FXMLNode(const std::string& name, FXMLNode* parent)
{
  this->name = name;
  this->parent = parent;
}

FXMLNode::~FXMLNode()
{
  while (!children.empty()) {
    FXMLNode *tmp = children.back();
    children.pop_back();
    delete tmp;
  }
}

void FXMLNode::appendChild(FXMLNode* node)
{
  this->children.push_back(node);
}

std::vector<FXMLNode*> FXMLNode::getChildNodes() const
{
  return children;
}

FXMLNode* FXMLNode::getParent() const
{
  return parent;
}

bool FXMLNode::hasChildNodes() const
{
  return !children.empty();
}
