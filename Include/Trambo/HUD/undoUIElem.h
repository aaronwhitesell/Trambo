#ifndef TRAMBO_UNDO_UI_ELEM_H
#define TRAMBO_UNDO_UI_ELEM_H

#include "buttonContainer.h"
#include "gameButton.h"
#include "../Resources/resourceHolder.h"

#include "../Events/eventHandler.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <string>


namespace sf
{
	class Color;
	class RenderStates;
	class RenderTarget;
	class RenderWindow;
	class Transform;
	class View;
}

namespace trmb
{

class Event;
class SoundPlayer;

class UndoUIElem : public sf::Transformable, public sf::Drawable , public EventHandler
{
public:
	using Callback = GameButton::Callback;
	using EventGuid = unsigned long;


public:
						UndoUIElem(Fonts::ID font, FontHolder& fonts, SoundEffects::ID soundEffect, SoundPlayer& soundPlayer
							, EventGuid leftClickPress, EventGuid leftClickRelease);
						UndoUIElem(const UndoUIElem&) = delete;
	UndoUIElem&			operator=(const UndoUIElem&) = delete;

	sf::Vector2f		getSize() const;

	void				setState(bool flag);
	void				setSize(sf::Vector2f size);
	void				setText(std::string doString, std::string undoString);
	void				setCharacterSize(unsigned int size);
	void				setCallbacks(Callback doCallback, Callback undoCallback);
	void				setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
							, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
							, sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
							, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
							, float outLineThickness);

	void				handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform);
	virtual void		handleEvent(const trmb::Event& gameEvent) override final;
	void				enable();
	void				disable();


private:
	using ButtonPtr = ButtonContainer::Ptr;


private:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void				standardizeCharacterSize();
	void				showButtons();
	void				restoreButtons();


private:
	const EventGuid		mLeftClickPress;	// ALW - Matches the GUID in the Controller class.
	const EventGuid		mLeftClickRelease;	// ALW - Matches the GUID in the Controller class.

	ButtonContainer		mContainer;
	ButtonPtr			mDoButton;
	ButtonPtr			mUndoButton;

	sf::Vector2f		mButtonSize;
	sf::Vector2f		mButtonPosition;
	std::string			mDoText;
	std::string			mUndoText;

	bool				mMouseOver;
	bool				mPressed;
	bool				mDisable;
	bool				mDoState;
};

void	centerOrigin(UndoUIElem& uiElem, bool centerXAxis = true, bool centerYAxis = true);

} // namespace trmb

#endif
