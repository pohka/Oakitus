#include "sample_gamemode.h"
#include <oak/event/event_manager.h>
#include "events/event_damage.h"
#include "sample_def.h"

using namespace oak;
using namespace sample;

void SampleGameMode::addEvents()
{
  EventManager::addEvent(EVENT_DAMAGE, sample::onDamageTaken);
}