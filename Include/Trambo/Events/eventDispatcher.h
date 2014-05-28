#ifndef TRAMBO_EVENTDISPATCHER_H
#define TRAMBO_EVENTDISPATCHER_H

#include <vector>


namespace trmb
{

class Event;
class EventHandler;

class EventDispatcher 
{
public:
	static EventDispatcher&		getInstance();
	void						registerListener(EventHandler* listener);
	void						unregisterListener(EventHandler const * listener);

	void						sendEvent(const Event& event) const;		// Sends event to all the registered listeners


private:
								EventDispatcher();							// available only to members and friends
								EventDispatcher(EventDispatcher const&);	// disallow copy constructor
								void operator=(EventDispatcher const&);		// disallow assignment operator


private:
	std::vector<EventHandler*> mListeners; // Component types of STL containers must be assignable (references are not)
};

} // namespace trmb

#endif
