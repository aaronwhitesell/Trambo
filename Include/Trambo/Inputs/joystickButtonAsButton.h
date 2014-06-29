#ifndef TRAMBO_JOYSTICKBUTTONASBUTTON_H
#define TRAMBO_JOYSTICKBUTTONASBUTTON_H

#include "action.h"

#include <memory>


namespace sf
{
	class Event;
}

namespace trmb
{

class JoystickButtonAsButton
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
							JoystickButtonAsButton(unsigned int button, ButtonType buttonType, unsigned int joystickId);

	unsigned int		    getInput() const;

	void					update(ActionWeakPtr actionWeakPtr);
	void					handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	typedef std::shared_ptr<Action> ActionSharedPtr;


private:
	void					realTime(ActionWeakPtr actionWeakPtr);
	void					onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);
	void					onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	unsigned int            mInput;
	ButtonType				mButtonType;
	unsigned int            mJoystickId;
};

} // namespace trmb

#endif
