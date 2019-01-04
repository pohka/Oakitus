#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "xml_node.h"
#include <string>

class XMLParser
{
  public:
    static XMLNode load(std::string file);
};

#endif