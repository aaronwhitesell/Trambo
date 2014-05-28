#include "../../../../Include/Trambo/Events/eventDispatcher.h"
#include "../../../../Include/Trambo/Events/eventHandler.h"

#include <algorithm>


namespace trmb
{

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
	mListeners.push_back(listener);
}

void EventDispatcher::unregisterListener(EventHandler const * listener)
{
	auto duplicateListener = std::remove_if(mListeners.begin(), mListeners.end(),
		[listener] (EventHandler const * element)
		{
			return listener == element;
		});

	mListeners.erase(duplicateListener, mListeners.end());
}

void EventDispatcher::sendEvent(const Event& event) const
{
	for (EventHandler* listener : mListeners)
		listener->handleEvent(event);
}

} // namespace trmb
