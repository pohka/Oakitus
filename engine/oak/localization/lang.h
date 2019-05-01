#pragma once
#ifndef LANG_H
#define LANG_H

#include <string>
#include <map>

namespace oak
{
  struct Lang
  {
    const std::string id; //2 charcater language codes using ISO 639-1
    const std::string nativeName;

    //list of ISO 639-1 language options
    static const std::map<std::string, std::string> ISO_STANDARDS;
  };
}

#endif