#ifndef TRAMBO_JOYSTICKAXISASBUTTON_H
#define TRAMBO_JOYSTICKAXISASBUTTON_H

#include "action.h"

#include <SFML/Window/Joystick.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace trmb
{

class JoystickAxisAsButton
{
public:
	typedef std::weak_ptr<Action> ActionWeakPtr;


public:
	enum class ButtonType
	{
		RealTime,
		OnPress,
		OnRelease,
	};


public:
							JoystickAxisAsButton(sf::Joystick::Axis axis, ButtonType buttonType, unsigned int joystickId, float onState, float offState);

	sf::Joystick::Axis		getInput() const;
	float					getOnState() const;
	float					getOffState() const;

	void					update(ActionWeakPtr actionWeakPtr);
	void					handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	typedef std::shared_ptr<Action> ActionSharedPtr;


private:
	enum class State
	{
		Off,
		On,
	};


private:
	void					realTime(ActionWeakPtr actionWeakPtr);
	void					onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);
	void					onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	sf::Joystick::Axis      mInput;
	ButtonType				mButtonType;
	unsigned int            mJoystickId;
	float					mOnState;
	float					mOffState;
	State					mPreviousState;
	State					mCurrentState;
};

} // namespace trmb

#endif
