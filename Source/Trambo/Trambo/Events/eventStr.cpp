#include "../../../../Include/Trambo/Events/eventStr.h"


namespace trmb
{

EventStr::EventStr(EventType type, std::string str)
: Event(type)
, mString(str)
{
}

std::string EventStr::getString() const
{
	return mString;
}

} // namespace trmb
