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
							// ALW - Allow copy construction and assignment

	EventType				getType() const;


private:
	EventType				mType;
};

} // namespace trmb

#endif
