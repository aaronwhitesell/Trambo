#ifndef TRAMBO_MOUSEBUTTONASBUTTON_H
#define TRAMBO_MOUSEBUTTONASBUTTON_H

#include "action.h"

#include <SFML/Window/mouse.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace trmb
{

class MouseButtonAsButton
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
							MouseButtonAsButton(sf::Mouse::Button button, ButtonType buttonType);

	sf::Mouse::Button		getInput() const;

	void					update(ActionWeakPtr actionWeakPtr);
	void					handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);

private:
	void					realTime(ActionWeakPtr actionWeakPtr);
	void					onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);
	void					onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	sf::Mouse::Button		mInput;
	ButtonType				mButtonType;
};

} // namespace trmb

#endif
