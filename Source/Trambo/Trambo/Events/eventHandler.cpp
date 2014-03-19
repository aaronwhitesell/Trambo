#include "../../../../Include/Trambo/Events/eventHandler.h"
#include "../../../../Include/Trambo/Events/eventDispatcher.h"


namespace trmb
{

EventHandler::EventHandler() 
{
	EventDispatcher::getInstance().registerListener(this);
}

void EventHandler::sendEvent(const Event& event) const
{
	EventDispatcher::getInstance().sendEvent(event);
}

} // namespace trmb