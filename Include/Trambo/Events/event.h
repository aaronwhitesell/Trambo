#ifndef TRAMBO_EVENT_H
#define TRAMBO_EVENT_H


namespace trmb
{

class Event
{
public:
	typedef unsigned long	EventType;


public:
	explicit				Event(EventType type);
							~Event();

	EventType				getType() const;


private:
	EventType				mType;
};

} // namespace trmb

#endif


// Example of a derived class of Event.
// Usage:
// const EventType myEvent = 0x496bf752;
// const trmb::Event& event = trmb::EventStr(myEvent, "my derived data");
// trmb::EventDispatcher::getInstance().sendEvent(event);
// Note, to use getString it is necessary to downcast
// const trmb::EventStr event = static_cast<const trmb::EventStr&>(e);
/*
#ifndef TRAMBO_EVENTSTR_H
#define TRAMBO_EVENTSTR_H


#include "event.h"

#include <string>

namespace trmb
{

class EventStr : public Event
{
public:
		typedef unsigned long	EventType;

public:
								EventStr(EventType type, std::string str);

	std::string			        getString() const;

private:
	std::string					mString;
};

} // namespace trmb

#endif
*/