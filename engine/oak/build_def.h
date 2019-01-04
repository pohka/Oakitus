

#ifndef BUILD_DEF_H
#define BUILD_DEF_H

  //target platform
  #ifdef _WIN32
    #define PLATFORM_WINDOWS 1
  #endif
  #ifdef __linux__
    #define PLATFORM_LINUX 1
  #endif


  //debug mode
  #ifdef _DEBUG
    #define DEBUG_MODE 1
  #else
    #ifdef DEBUG_MODE_ENABLED
      #define DEBUG_MODE 1
    #endif
  #endif

#endif