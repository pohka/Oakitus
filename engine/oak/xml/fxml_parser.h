#pragma once
#ifndef FXML_PARSER_H
#define FXML_PARSER_H

#include "fxml_node.h"
#include <string>

namespace oak
{
  //fast xml parser, doesn't parse attributes and only leaf nodes can have content
  class FXMLParser
  {
  public:
    static FXMLNode load(const std::string& file);
  };
}

#endif