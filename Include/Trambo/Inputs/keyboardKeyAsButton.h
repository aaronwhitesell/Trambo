#ifndef TRAMBO_KEYBOARDKEYASBUTTON_H
#define TRAMBO_KEYBOARDKEYASBUTTON_H

#include "action.h"

#include <SFML/Window/Keyboard.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace trmb
{

class KeyboardKeyAsButton
{
public:
	typedef unsigned long EventGuid;
	typedef std::shared_ptr<Action> ActionSharedPtr;
	typedef std::weak_ptr<Action> ActionWeakPtr;


public:
	enum class ButtonType
	{
		RealTime,
		OnPress,
		OnRelease,
	};


public:
							KeyboardKeyAsButton(sf::Keyboard::Key key, ButtonType buttonType);

	sf::Keyboard::Key		getInput() const;

	void					update(ActionWeakPtr actionWeakPtr);
	void					handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);

private:
	void					KeyboardKeyAsButton::realTime(ActionWeakPtr actionWeakPtr);
	void					KeyboardKeyAsButton::onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);
	void					KeyboardKeyAsButton::onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	sf::Keyboard::Key		mInput;
	ButtonType				mButtonType;
};

} // namespace trmb

#endif