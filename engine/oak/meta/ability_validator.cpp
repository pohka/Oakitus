#include <oak/meta/ability_validator.h>
#include <oak/meta/meta_data.h>

using namespace oak;

void AbilityValidator::validate()
{


  auto data = MetaData::getData(META_DATA_KEY_ABILITYS);
 
  //iterate through each ability
  for (auto it = data.begin(); it != data.end(); it++)
  {
    auto abil = it.value();
    //for(auto abilIter=0;)
  }
}