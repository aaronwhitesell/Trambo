#ifndef TRAMBO_EVENT_STR_H
#define TRAMBO_EVENT_STR_H

#include "event.h"

#include <string>


namespace trmb
{

class EventStr : public Event
{
// Usage:
// const EventType myEvent = 0x496bf752;
// const trmb::Event& event = trmb::EventStr(myEvent, "my derived data");
// trmb::EventDispatcher::getInstance().sendEvent(event);
// Note, to use getString it is necessary to downcast
// const trmb::EventStr eventStr = static_cast<const trmb::EventStr&>(event);
public:
	typedef unsigned long	EventType;


public:
								EventStr(EventType type, std::string str);
								// ALW - Allow copy construction and assignment

	std::string					getString() const;


private:
	std::string					mString;
};

} // namespace trmb

#endif
