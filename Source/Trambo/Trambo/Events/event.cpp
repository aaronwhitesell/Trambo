#include "../../../../Include/Trambo/Events/event.h"


using namespace trmb;

Event::Event(EventType type)
: mType(type)
{
}

Event::~Event()
{
}

Event::EventType Event::getType() const
{
	return mType;
}


// Example of a derived class of Event.
/*
#include "../../../../Include/Trambo/Events/eventStr.h"


using namespace trmb;

EventStr::EventStr(EventType type, std::string str)
: Event(type)
, mString(str)
{
}

std::string EventStr::getString() const
{
	return mString;
}
*/