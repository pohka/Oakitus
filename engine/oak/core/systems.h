#pragma once
#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <oak/localization/i_localization.h>
#include <oak/localization/localization.h>

namespace oak
{
  //namespace for systems
  namespace systems
  {
    //localized string data
    ILocalization* StringData = new Localization();
  }
}

#endif