#include "../../../../Include/Trambo/Inputs/actionBinding.h"

#include <algorithm>
#include <cassert>


namespace trmb
{

void ActionBinding::update()
{
	for (auto& element : mKeyboardKeysAsButtonBindings)
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
			return keyboardKeyAsButton.getInput() == element.first.getInput(); 
		});

	mKeyboardKeysAsButtonBindings.erase(duplicateKeys, mKeyboardKeysAsButtonBindings.end());

	// ALW - Remove duplicate actions
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

	// ALW - Push new element binding onto vector
	mKeyboardKeysAsButtonBindings.emplace_back(KeyboardKeyAsButton(keyboardKeyAsButton), getWeakPtrToAction(eventGuid));
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
