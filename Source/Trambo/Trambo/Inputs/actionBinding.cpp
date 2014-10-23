#include "../../../../Include/Trambo/Inputs/actionBinding.h"

#include <algorithm>
#include <cassert>


namespace trmb
{

ActionBinding::ActionBinding()
{
}

const std::vector<ActionBinding::ActionSharedPtr>& ActionBinding::getActions() const
{
	return mActions;
}

sf::Keyboard::Key ActionBinding::getInputFromKeyboardKeyAsButtonBinding(EventGuid eventGuid) const
{
	for (const auto& element : mKeyboardKeysAsButtonBindings)
	{
		ActionSharedPtr action = element.second.lock(); // ALW - get shared_ptr from weak_ptr
		if (!action)
		{
			assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
		}

		if (eventGuid == action->getGameEvent().getType())
		{
			return element.first.getInput();
		}
	}

	// ALW - Hack - Allows check to be made, if action does not correspond to a button.
	return sf::Keyboard::Unknown;
}

sf::Mouse::Button ActionBinding::getInputFromMouseButtonAsButtonBinding(EventGuid eventGuid) const
{
	for (const auto& element : mMouseButtonsAsButtonBindings)
	{
		ActionSharedPtr action = element.second.lock(); // ALW - get shared_ptr from weak_ptr
		if (!action)
		{
			assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
		}

		if (eventGuid == action->getGameEvent().getType())
		{
			return element.first.getInput();
		}
	}

	// ALW - Hack - Allows check to be made, if action does not correspond to a button.
	return sf::Mouse::Button::ButtonCount;
}

void ActionBinding::update()
{
	for (auto& element : mKeyboardKeysAsButtonBindings)
	{
		element.first.update(element.second);
	}

	for (auto& element : mMouseButtonsAsButtonBindings)
	{
		element.first.update(element.second);
	}

	for (auto& element : mJoystickButtonsAsButtonBindings)
	{
		element.first.update(element.second);
	}

	for (auto& element : mJoystickAxesAsButtonBindings)
	{
		element.first.update(element.second);
	}
}

void ActionBinding::handleEvent(const sf::Event& inputEvent)
{
	for (auto& element : mKeyboardKeysAsButtonBindings)
	{
		element.first.handleEvent(inputEvent, element.second);
	}

	for (auto& element : mMouseButtonsAsButtonBindings)
	{
		element.first.handleEvent(inputEvent, element.second);
	}

	for (auto& element : mJoystickButtonsAsButtonBindings)
	{
		element.first.handleEvent(inputEvent, element.second);
	}

	for (auto& element : mJoystickAxesAsButtonBindings)
	{
		element.first.handleEvent(inputEvent, element.second);
	}
}

void ActionBinding::createAction(EventGuid eventGuid)
{
	// ALW - Remove duplicate actions
	auto duplicateActions = std::remove_if(begin(mActions), end(mActions), 
		[eventGuid] (ActionSharedPtr element)
		{ 
			return eventGuid == element->getGameEvent().getType();
		});

	mActions.erase(duplicateActions, mActions.end());

	// ALW - Register listener. Will unregister listener when element's share_ptr ref goes to zero.
	mActions.emplace_back(ActionSharedPtr(std::make_shared<Action>(eventGuid)));
}

void ActionBinding::assignKeyboardKeyAsButtonBinding(const KeyboardKeyAsButton& keyboardKeyAsButton, EventGuid eventGuid)
{
	// ALW - Remove duplicate keys
	auto duplicateKeys = std::remove_if(begin(mKeyboardKeysAsButtonBindings), end(mKeyboardKeysAsButtonBindings), 
		[&keyboardKeyAsButton] (const std::pair<KeyboardKeyAsButton, ActionWeakPtr>& element)
		{ 
			// ALW - A button is considered a duplicate if both the input and the button type are the same.
			return keyboardKeyAsButton.getInput() == element.first.getInput()
				&& keyboardKeyAsButton.getButtonType() == element.first.getButtonType();
		});

	mKeyboardKeysAsButtonBindings.erase(duplicateKeys, mKeyboardKeysAsButtonBindings.end());

	// ALW - Remove duplicate actions
	removeDuplicateActionsInKeyboardKeysAsButtonBindings(eventGuid);
	removeDuplicateActionsInMouseButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickAxesAsButtonBindings(eventGuid);

	// ALW - Push new element binding onto vector
	mKeyboardKeysAsButtonBindings.emplace_back(KeyboardKeyAsButton(keyboardKeyAsButton), getWeakPtrToAction(eventGuid));
}

void ActionBinding::assignMouseButtonAsButtonBinding(const MouseButtonAsButton& mouseButtonAsButton, EventGuid eventGuid)
{
	// ALW - Remove duplicate buttons
	auto duplicateButtons = std::remove_if(begin(mMouseButtonsAsButtonBindings), end(mMouseButtonsAsButtonBindings),
		[&mouseButtonAsButton] (const std::pair<MouseButtonAsButton, ActionWeakPtr>& element)
		{
			// ALW - A button is considered a duplicate if both the input and the button type are the same.
			return mouseButtonAsButton.getInput() == element.first.getInput()
				&& mouseButtonAsButton.getButtonType() == element.first.getButtonType();
		});

	mMouseButtonsAsButtonBindings.erase(duplicateButtons, mMouseButtonsAsButtonBindings.end());

	// ALW - Remove duplicate actions
	removeDuplicateActionsInKeyboardKeysAsButtonBindings(eventGuid);
	removeDuplicateActionsInMouseButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickAxesAsButtonBindings(eventGuid);

	// ALW - Push new element binding onto vector
	mMouseButtonsAsButtonBindings.emplace_back(MouseButtonAsButton(mouseButtonAsButton), getWeakPtrToAction(eventGuid));
}

void ActionBinding::assignJoystickButtonAsButtonBinding(const JoystickButtonAsButton& joystickButtonAsButton, EventGuid eventGuid)
{
	// ALW - Remove duplicate buttons
	auto duplicateButtons = std::remove_if(begin(mJoystickButtonsAsButtonBindings), end(mJoystickButtonsAsButtonBindings),
		[&joystickButtonAsButton] (const std::pair<JoystickButtonAsButton, ActionWeakPtr>& element)
		{
			// ALW - A button is considered a duplicate if both the input and the button type are the same.
			return joystickButtonAsButton.getInput() == element.first.getInput()
				&& joystickButtonAsButton.getButtonType() == element.first.getButtonType();
		});

	mJoystickButtonsAsButtonBindings.erase(duplicateButtons, mJoystickButtonsAsButtonBindings.end());

	// ALW - Remove duplicate actions
	removeDuplicateActionsInKeyboardKeysAsButtonBindings(eventGuid);
	removeDuplicateActionsInMouseButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickAxesAsButtonBindings(eventGuid);

	// ALW - Push new element binding onto vector
	mJoystickButtonsAsButtonBindings.emplace_back(JoystickButtonAsButton(joystickButtonAsButton), getWeakPtrToAction(eventGuid));
}

void ActionBinding::assignJoystickAxisAsButtonBinding(const JoystickAxisAsButton& joystickAxisAsButton, EventGuid eventGuid)
{
	// ALW - Remove duplicate axes with the same ranges
	auto duplicateButtons = std::remove_if(begin(mJoystickAxesAsButtonBindings), end(mJoystickAxesAsButtonBindings),
		[&joystickAxisAsButton] (const std::pair<JoystickAxisAsButton, ActionWeakPtr>& element)
		{
			// ALW - An axis is considered a duplicate if the input, button type, and states are the same.
			return joystickAxisAsButton.getInput() == element.first.getInput()
				&& joystickAxisAsButton.getButtonType() == element.first.getButtonType()
				&& joystickAxisAsButton.getOnState() == element.first.getOnState()
				&& joystickAxisAsButton.getOffState() == element.first.getOffState();
		});

	mJoystickAxesAsButtonBindings.erase(duplicateButtons, mJoystickAxesAsButtonBindings.end());

	// ALW - Remove duplicate actions
	removeDuplicateActionsInKeyboardKeysAsButtonBindings(eventGuid);
	removeDuplicateActionsInMouseButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickButtonsAsButtonBindings(eventGuid);
	removeDuplicateActionsInJoystickAxesAsButtonBindings(eventGuid);

	// ALW - Push new element binding onto vector
	mJoystickAxesAsButtonBindings.emplace_back(JoystickAxisAsButton(joystickAxisAsButton), getWeakPtrToAction(eventGuid));
}

void ActionBinding::removeDuplicateActionsInKeyboardKeysAsButtonBindings(EventGuid eventGuid)
{
	auto duplicateActions = std::remove_if(begin(mKeyboardKeysAsButtonBindings), end(mKeyboardKeysAsButtonBindings), 
		[eventGuid] (const std::pair<KeyboardKeyAsButton, ActionWeakPtr>& element)
		{ 
			ActionSharedPtr action = element.second.lock(); // ALW - get shared_ptr from weak_ptr
			if (!action)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			return eventGuid == action->getGameEvent().getType(); 
		});

	mKeyboardKeysAsButtonBindings.erase(duplicateActions, mKeyboardKeysAsButtonBindings.end());
}

void ActionBinding::removeDuplicateActionsInMouseButtonsAsButtonBindings(EventGuid eventGuid)
{
	auto duplicateActions = std::remove_if(begin(mMouseButtonsAsButtonBindings), end(mMouseButtonsAsButtonBindings),
		[eventGuid] (const std::pair<MouseButtonAsButton, ActionWeakPtr>& element)
		{
			ActionSharedPtr action = element.second.lock(); // ALW - get shared_ptr from weak_ptr
			if (!action)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			return eventGuid == action->getGameEvent().getType();
		});

	mMouseButtonsAsButtonBindings.erase(duplicateActions, mMouseButtonsAsButtonBindings.end());
}

void ActionBinding::removeDuplicateActionsInJoystickButtonsAsButtonBindings(EventGuid eventGuid)
{
	auto duplicateActions = std::remove_if(begin(mJoystickButtonsAsButtonBindings), end(mJoystickButtonsAsButtonBindings),
		[eventGuid] (const std::pair<JoystickButtonAsButton, ActionWeakPtr>& element)
		{
			ActionSharedPtr action = element.second.lock(); // ALW - get shared_ptr from weak_ptr
			if (!action)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			return eventGuid == action->getGameEvent().getType();
		});

	mJoystickButtonsAsButtonBindings.erase(duplicateActions, mJoystickButtonsAsButtonBindings.end());
}

void ActionBinding::removeDuplicateActionsInJoystickAxesAsButtonBindings(EventGuid eventGuid)
{
	auto duplicateActions = std::remove_if(begin(mJoystickAxesAsButtonBindings), end(mJoystickAxesAsButtonBindings),
		[eventGuid] (const std::pair<JoystickAxisAsButton, ActionWeakPtr>& element)
		{
			ActionSharedPtr action = element.second.lock(); // ALW - get shared_ptr from weak_ptr
			if (!action)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			return eventGuid == action->getGameEvent().getType();
		});

	mJoystickAxesAsButtonBindings.erase(duplicateActions, mJoystickAxesAsButtonBindings.end());
}

ActionBinding::ActionWeakPtr ActionBinding::getWeakPtrToAction(EventGuid eventGuid) const
{
	auto ret = std::find_if(begin(mActions), end(mActions),
		[eventGuid] (ActionSharedPtr element)
		{
			return eventGuid == element->getGameEvent().getType();
		});

	if (ret == end(mActions))
	{
		assert(("Logic Error: The eventGuid does not correspond to an action in mActions!", false));
	}

	return *ret;
}

} // namespace trmb
