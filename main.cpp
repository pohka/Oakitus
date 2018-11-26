#include "oak/setup.h"

using namespace oak;

int main()
{
  Oakitus::init();
  return 0;
}


void Oakitus::load()
{
  Scene::loadFirstScene(*new Scene());
}

