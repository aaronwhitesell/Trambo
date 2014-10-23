#include "../../../../Include/Trambo/Inputs/mouseButtonAsButton.h"
#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Window/Event.hpp>

#include <cassert>


namespace trmb
{

MouseButtonAsButton::MouseButtonAsButton(sf::Mouse::Button button, ButtonType buttonType)
: mInput(button)
, mButtonType(buttonType)
{
}

sf::Mouse::Button MouseButtonAsButton::getInput() const
{
	return mInput;
}

MouseButtonAsButton::ButtonType MouseButtonAsButton::getButtonType() const
{
	return mButtonType;
}

void MouseButtonAsButton::update(ActionWeakPtr actionWeakPtr)
{
	realTime(actionWeakPtr);
}

void MouseButtonAsButton::handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	onPress(inputEvent, actionWeakPtr);
	onRelease(inputEvent, actionWeakPtr);
}

void MouseButtonAsButton::realTime(ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::RealTime == mButtonType)
	{
		if (sf::Mouse::isButtonPressed(mInput))
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

void MouseButtonAsButton::onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnPress == mButtonType)
	{
		if (mInput == inputEvent.mouseButton.button && sf::Event::MouseButtonPressed == inputEvent.type)
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

void MouseButtonAsButton::onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnRelease == mButtonType)
	{
		if (mInput == inputEvent.mouseButton.button && sf::Event::MouseButtonReleased == inputEvent.type)
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
