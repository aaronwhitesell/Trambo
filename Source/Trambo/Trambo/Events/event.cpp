#include "../../../../Include/Trambo/Events/event.h"


namespace trmb
{

Event::Event(EventType type)
: mType(type)
{
}

Event::EventType Event::getType() const
{
	return mType;
}

} // namespace trmb
