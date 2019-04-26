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

