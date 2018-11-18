#include "xml_node.h"

XMLNode::XMLNode(std::string name, XMLNode* parent)
{
  this->name = name;
  this->parent = parent;
}

XMLNode::~XMLNode()
{
  while (!children.empty()) {
    XMLNode *tmp = children.back();
    children.pop_back();
    delete tmp;
  }
}

void XMLNode::appendChild(XMLNode* node)
{
  this->children.push_back(node);
}

std::vector<XMLNode*> XMLNode::getChildNodes()
{
  return children;
}

XMLNode* XMLNode::getParent()
{
  return parent;
}

bool XMLNode::hasChildNodes()
{
  return !children.empty();
}
