#ifndef META_H
#define META_H

#include <string>
#include <oak/core/kvmap.h>
#include "meta_def.h"
#include "var_object.h"

namespace oak
{
  //meta data, loading and accessing
  struct Meta
  {
    //load a meta file
    static void load(const char* filepath);

    //var_object loaded from meta files
    static kvmap<std::string, var_object*> objs;

  private:
    //get directory of executable
    static std::string dir();

    //parse the content of a meta file
    static void parse(std::string& content, unsigned int& index);

    //parsing states
    static cnum STATE_BEFORE_OBJ = 0;
    static cnum STATE_OBJ = 1;
    static cnum STATE_AFTER_OBJ = 2;
    static cnum STATE_BEFORE_KEY = 3;
    static cnum STATE_KEY = 4;
    static cnum STATE_AFTER_KEY = 5;
    static cnum STATE_BEFORE_VAL = 6;
    static cnum STATE_VAL = 7;
    static cnum STATE_AFTER_VAL = 8;
  };
}

#endif