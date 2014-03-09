#include "../../../../Include/Trambo/Events/eventDispatcher.h"
#include "../../../../Include/Trambo/Events/eventHandler.h"

using namespace trmb;

EventDispatcher::EventDispatcher() 
{
}

EventDispatcher& EventDispatcher::getInstance() 
{
	static EventDispatcher mInstance;
	return mInstance;
}

void EventDispatcher::registerListener(EventHandler* listener) 
{
	mListenerList.push_back(listener);
}

void EventDispatcher::sendEvent(const Event& event) const
{
	for (EventHandler* listener : mListenerList)
		listener->handleEvent(event);
}
