#ifndef TRAMBO_ACTIONBINDING_H
#define TRAMBO_ACTIONBINDING_H

#include "../Inputs/action.h"
#include "../Inputs/keyboardKeyAsButton.h"
#include "../Inputs/MouseButtonAsButton.h"

#include <memory>
#include <utility>
#include <vector>


namespace sf
{
	class Event;
}

namespace trmb
{

class ActionBinding
{
public:
	typedef unsigned long EventGuid;
	typedef std::shared_ptr<Action> ActionSharedPtr;
	typedef std::weak_ptr<Action> ActionWeakPtr;


public:
	void					update();
	void					handleEvent(const sf::Event& inputEvent);

	void					createAction(EventGuid eventGuid);
	void					assignKeyboardKeyAsButtonBinding(const KeyboardKeyAsButton& keyboardKeyAsButton, EventGuid eventGuid);
	void					assignMouseButtonAsButtonBinding(const MouseButtonAsButton& mouseButtonAsButton, EventGuid eventGuid);


private:
	void					removeDuplicateActionsInKeyboardKeysAsButtonBindings(EventGuid eventGuid);
	void					removeDuplicateActionsInMouseButtonsAsButtonBindings(EventGuid eventGuid);

	ActionWeakPtr			getWeakPtrToAction(EventGuid eventGuid) const;


private:
	std::vector<ActionSharedPtr>								mActions; // ALW - Once added, elements should not be deleted.
	std::vector<std::pair<KeyboardKeyAsButton, ActionWeakPtr>>	mKeyboardKeysAsButtonBindings;
	std::vector<std::pair<MouseButtonAsButton, ActionWeakPtr>>	mMouseButtonsAsButtonBindings;
};

} // namespace trmb

#endif