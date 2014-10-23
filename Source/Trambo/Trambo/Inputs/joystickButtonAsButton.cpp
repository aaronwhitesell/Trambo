#include "../../../../Include/Trambo/Inputs/joystickButtonAsButton.h"
#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>

#include <cassert>


namespace trmb
{

JoystickButtonAsButton::JoystickButtonAsButton(unsigned int button, ButtonType buttonType, unsigned int joystickId)
: mInput(button)
, mButtonType(buttonType)
, mJoystickId(joystickId)
{
	assert(sf::Joystick::ButtonCount > button);
}

unsigned int JoystickButtonAsButton::getInput() const
{
	return mInput;
}

JoystickButtonAsButton::ButtonType JoystickButtonAsButton::getButtonType() const
{
	return mButtonType;
}

void JoystickButtonAsButton::update(ActionWeakPtr actionWeakPtr)
{
	realTime(actionWeakPtr);
}

void JoystickButtonAsButton::handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	onPress(inputEvent, actionWeakPtr);
	onRelease(inputEvent, actionWeakPtr);
}

void JoystickButtonAsButton::realTime(ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::RealTime == mButtonType)
	{
		if (sf::Joystick::isButtonPressed(mJoystickId, mInput))
		{
			ActionSharedPtr actionSharedPtr = actionWeakPtr.lock(); // ALW - get shared_ptr from weak_ptr
			if (!actionSharedPtr)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			actionSharedPtr->sendEvent();
		}
	}
}

void JoystickButtonAsButton::onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnPress == mButtonType && mJoystickId == inputEvent.joystickButton.joystickId)
	{
		if (mInput == inputEvent.joystickButton.button && sf::Event::JoystickButtonPressed == inputEvent.type)
		{
			ActionSharedPtr actionSharedPtr = actionWeakPtr.lock(); // ALW - get shared_ptr from weak_ptr
			if (!actionSharedPtr)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			actionSharedPtr->sendEvent();
		}
	}
}

void JoystickButtonAsButton::onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnRelease == mButtonType && mJoystickId == inputEvent.joystickButton.joystickId)
	{
		if (mInput == inputEvent.joystickButton.button && sf::Event::JoystickButtonReleased == inputEvent.type)
		{
			ActionSharedPtr actionSharedPtr = actionWeakPtr.lock(); // ALW - get shared_ptr from weak_ptr
			if (!actionSharedPtr)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			actionSharedPtr->sendEvent();
		}
	}
}

} // namespace trmb
