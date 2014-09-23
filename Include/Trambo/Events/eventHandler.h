#ifndef TRAMBO_EVENTHANDLER_H
#define TRAMBO_EVENTHANDLER_H


namespace trmb
{

class Event;

class EventHandler 
{
public:
							EventHandler();
							EventHandler(const EventHandler&) = delete;
	EventHandler&			operator=(const EventHandler&) = delete;
	virtual					~EventHandler();

	virtual void			handleEvent(const Event& event) = 0;


protected:
	void					sendEvent(const Event& event) const;   // Sends event to all the registered listeners
};

} // trmb namespace

#endif