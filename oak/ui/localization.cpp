#include "localization.h"

using namespace oak::ui;

std::map<uint, std::string> Localization::strings;

void Localization::addString(const uint id, std::string value)
{
  strings.insert(std::pair<uint, std::string>(id, value));
}