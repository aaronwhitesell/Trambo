#include "../../../../Include/Trambo/Inputs/keyboardKeyAsButton.h"

#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Window/Event.hpp>

#include <cassert>


namespace trmb
{

KeyboardKeyAsButton::KeyboardKeyAsButton(sf::Keyboard::Key key, ButtonType buttonType)
: mInput(key)
, mButtonType(buttonType)
{
}

sf::Keyboard::Key KeyboardKeyAsButton::getInput() const
{
	return mInput;
}

void KeyboardKeyAsButton::update(ActionWeakPtr actionWeakPtr)
{
	realTime(actionWeakPtr);
}

void KeyboardKeyAsButton::handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	onPress(inputEvent, actionWeakPtr);
	onRelease(inputEvent, actionWeakPtr);
}

void KeyboardKeyAsButton::realTime(ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::RealTime == mButtonType)
	{
		if (sf::Keyboard::isKeyPressed(mInput))
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

void KeyboardKeyAsButton::onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnPress == mButtonType)
	{
		if (mInput == inputEvent.key.code && sf::Event::KeyPressed == inputEvent.type)
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

void KeyboardKeyAsButton::onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnRelease == mButtonType)
	{
		if (mInput == inputEvent.key.code && sf::Event::KeyReleased == inputEvent.type)
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
