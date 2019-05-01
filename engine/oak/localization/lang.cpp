#include <oak/localization/lang.h>

//list of _ISO_639-1 options
const std::map<std::string, std::string> oak::Lang::ISO_STANDARDS =
{
  { "en", "english" }, //english
  { "de", "deutsch" }, //german
  { "es", "español" }, //spanish
  { "zh", "	中文" }, //chinese
  { "fr", "français"}, //french
  { "ja", "日本語" }, //japanese
  { "sv", "svenska"} //sweedish
};
