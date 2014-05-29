#include "../../../../Include/Trambo/Inputs/action.h"


namespace trmb
{

Action::Action(const EventGuid eventGuid)
: mGameEvent(Event(eventGuid))
{
}

Action::Action(const Event& gameEvent)
: mGameEvent(gameEvent)
{
}

const Event& Action::getGameEvent() const
{
	return mGameEvent;
}

void Action::sendEvent() const
{
	EventHandler::sendEvent(mGameEvent);
}

void Action::handleEvent(const Event&)
{
	// ALW - The Action class does not handle events.  It only sends them.
}

} // namespace trmb
