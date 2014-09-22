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
							// ALW - Allow copy construction and assignment

	sf::Mouse::Button		getInput() const;

	void					update(ActionWeakPtr actionWeakPtr);
	void					handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr);


private:
	typedef std::shared_ptr<Action> ActionSharedPtr;


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
