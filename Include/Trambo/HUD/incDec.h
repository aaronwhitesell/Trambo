#ifndef TRAMBO_INC_DEC_H
#define TRAMBO_INC_DEC_H

#include "buttonContainer.h"
#include "gameButton.h"
#include "../Resources/resourceHolder.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>


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

class SoundPlayer;

class IncDec : public sf::Transformable, public sf::Drawable
{
public:
	using Callback = GameButton::Callback;
	using EventGuid = unsigned long;


public:
							IncDec(Fonts::ID fontID, FontHolder& fonts, SoundEffects::ID soundID, SoundPlayer& sounds
								, EventGuid leftClickPress, EventGuid leftClickRelease, sf::Vector2f size = sf::Vector2f(20.0f, 20.0f));
							IncDec(const IncDec&) = delete;
	IncDec&					operator=(const IncDec&) = delete;

	sf::Vector2f			getSize() const;

	void					setHorizontalBuffer(float buffer);
	void					setCallbacks(Callback increment, Callback decrement);
	void					setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
								, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
								, sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
								, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
								, float outLineThickness);

	void					handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform);
	void					enable();
	void					disable();
	void					unhide();
	void					hide();


private:
	using ButtonPtr = ButtonContainer::Ptr;


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	
private:
	ButtonContainer			mButtons;
	float					mHorizontalBuffer;
	ButtonPtr				mIncrementButton;
	ButtonPtr				mDecrementButton;
	bool					mDisable;
};

void	centerOrigin(IncDec& ui, bool centerXAxis = true, bool centerYAxis = true);

} // namespace trmb

#endif
