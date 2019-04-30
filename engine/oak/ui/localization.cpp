#include "localization.h"

using namespace ion;

std::map<uint, std::string> Localization::strings;

void Localization::addString(uint id, std::string value)
{
  strings.insert(std::pair<uint, std::string>(id, value));
}