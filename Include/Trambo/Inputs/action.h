#ifndef TRAMBO_ACTION_H
#define TRAMBO_ACTION_H

#include "../Events/event.h"
#include "../Events/eventHandler.h"


namespace trmb
{

class Action : public EventHandler
{
public:
	typedef unsigned long EventGuid;


public:
	explicit				Action(EventGuid eventGuid);
	explicit				Action(const Event& gameEvent);

	const Event&			getGameEvent() const;

	void					sendEvent() const;
	virtual void			handleEvent(const Event&) final; // ALW - The Action class does not handle events.  It only sends them.


private:
	Event					mGameEvent;
};

} // namespace trmb

#endif
