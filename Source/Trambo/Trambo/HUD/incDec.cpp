#include "../../../../Include/Trambo/HUD/IncDec.h"
#include "../../../../Include/Trambo/Sounds/soundPlayer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>

#include <cassert>


namespace trmb
{

IncDec::IncDec(Fonts::ID fontID, FontHolder& fonts, SoundEffects::ID soundID, SoundPlayer& sounds
	, EventGuid leftClickPress, EventGuid leftClickRelease, sf::Vector2f size)
: mButtons(leftClickPress, leftClickRelease)
, mHorizontalBuffer(1.0f)
{
	mIncrementButton = std::make_shared<GameButton>(fontID, fonts, soundID, sounds, size);
	mIncrementButton->setPosition(0.0f, 0.0f);
	mIncrementButton->setText("+");

	mDecrementButton = std::make_shared<GameButton>(fontID, fonts, soundID, sounds, size);
	mDecrementButton->setPosition(mIncrementButton->getSize().x + mHorizontalBuffer, 0.0f);
	mDecrementButton->setText("-");

	mButtons.pack(mIncrementButton);
	mButtons.pack(mDecrementButton);
}

sf::Vector2f IncDec::getSize() const
{
	assert(("ALW - Logic Error: The increment button's height is not the same as the decrement button's height!"
		, mIncrementButton->getSize().y == mDecrementButton->getSize().y));

	return sf::Vector2f(mIncrementButton->getSize().x + mHorizontalBuffer + mDecrementButton->getSize().x, mIncrementButton->getSize().y);
}

void IncDec::setCallbacks(Callback increment, Callback decrement)
{
	mIncrementButton->setCallback(increment);
	mDecrementButton->setCallback(decrement);
}

void IncDec::setHorizontalBuffer(float buffer)
{
	mHorizontalBuffer = buffer;
	mDecrementButton->setPosition(mIncrementButton->getSize().x + mHorizontalBuffer, 0.0f);
}

void IncDec::setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
		, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
	    , sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
		, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
		, float outLineThickness)
{
	mButtons.setVisualScheme(backgroundColor, textColor, outlineColor
		, hoverBackgroundColor, hoverTextColor, hoverOutlineColor
		, depressBackgroundColor, depressTextColor, depressOutlineColor
		, disableBackgroundColor, disableTextColor, disableOutlineColor
		, outLineThickness);
}

void IncDec::handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform)
{
	sf::Transform combinedTransform = getTransform() * transform;

	mButtons.handler(window, view, combinedTransform);
}

void IncDec::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mButtons, states);
}

void centerOrigin(IncDec& ui, bool centerXAxis, bool centerYAxis)
{
	sf::Vector2f size = ui.getSize();
	float xAxis = 0.0f;
	float yAxis = 0.0f;

	if (centerXAxis)
		xAxis = std::floor(size.x / 2.0f);

	if (centerYAxis)
		yAxis = std::floor(size.y / 2.0f);

	ui.setOrigin(xAxis, yAxis);
}

} // namespace trmb
