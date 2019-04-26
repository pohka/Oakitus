#include "xml_node.h"

using namespace oak;

XMLNode::XMLNode()
{

}

XMLNode::~XMLNode()
{
  {
    for (auto i : children)
    {
      delete i;
    }
  }
}


const std::map<std::string, std::string>& XMLNode::getAttrs() const
{
  return attrs;
}

std::string XMLNode::getAttr(const std::string& key) const
{
  auto it = attrs.find(key);
  if (it != attrs.end())
  {
    return it->second;
  }

  return "";
}

bool XMLNode::hasAttr(const std::string& key) const
{
  auto it = attrs.find(key);
  return it != attrs.end();
}

const std::string& XMLNode::getTag() const
{
  return tag;
}

const std::string& XMLNode::getTextContent() const
{
  return text;
}

void XMLNode::setTextContent(const std::string& text)
{
  this->text = text;
}


const std::vector<XMLNode*>& XMLNode::getChildNodes() const
{
  return children;
}


void XMLNode::addChildNode(XMLNode* node)
{
  node->parent = this;
  children.push_back(node);
}

void XMLNode::setAttr(const std::string& key, const std::string& value)
{
  attrs[key] = value;
}

void XMLNode::setTag(const std::string& tag)
{
  this->tag = tag;
}
