#include "../../../../Include/Trambo/HUD/UndoUIElem.h"
#include "../../../../Include/Trambo/Events/event.h"
#include "../../../../Include/Trambo/Sounds/soundPlayer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>

#include <cassert>


namespace trmb
{

UndoUIElem::UndoUIElem(Fonts::ID font, FontHolder& fonts, SoundEffects::ID soundEffect, SoundPlayer& soundPlayer
	, EventGuid leftClickPress, EventGuid leftClickRelease)
: mLeftClickPress(leftClickPress)
, mLeftClickRelease(leftClickRelease)
, mContainer(leftClickPress, leftClickRelease)
, mButtonSize(sf::Vector2f(50.0f, 20.0f))
, mButtonPosition(sf::Vector2f(0.0f, 0.0f))
, mMouseOver(false)
, mPressed(false)
, mDoState(true)
{
	mDoButton = std::make_shared<GameButton>(font, fonts, soundEffect, soundPlayer);
	mDoButton->setSize(mButtonSize);
	mDoButton->setPosition(mButtonPosition);

	mUndoButton = std::make_shared<GameButton>(font, fonts, soundEffect, soundPlayer);
	mUndoButton->setSize(sf::Vector2f(0.0f, 0.0f) , false);
	mUndoButton->setPosition(mButtonPosition);

	mContainer.pack(mDoButton);
	mContainer.pack(mUndoButton);
}

sf::Vector2f UndoUIElem::getSize() const
{
	return mButtonSize;
}

void UndoUIElem::setSize(sf::Vector2f size)
{
	mButtonSize = size;

	standardizeCharacterSize();
}

void UndoUIElem::setText(std::string doString, std::string undoString)
{
	mDoText = doString;
	mUndoText = undoString;

	standardizeCharacterSize();
}

void UndoUIElem::setCallbacks(Callback doCallback, Callback undoCallback)
{
	mDoButton->setCallback(doCallback);
	mUndoButton->setCallback(undoCallback);
}

void UndoUIElem::setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
		, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
	    , sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
		, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
		, float outLineThickness)
{
	mContainer.setVisualScheme(backgroundColor, textColor, outlineColor
		, hoverBackgroundColor, hoverTextColor, hoverOutlineColor
		, depressBackgroundColor, depressTextColor, depressOutlineColor
		, disableBackgroundColor, disableTextColor, disableOutlineColor
		, outLineThickness);
}

void UndoUIElem::handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform)
{
	const sf::Vector2i relativeToWindow = sf::Mouse::getPosition(window);
	const sf::Vector2f relativeToWorld = window.mapPixelToCoords(relativeToWindow, view);
	const sf::Vector2f mousePosition = relativeToWorld;

	assert(("ALW - Logic Error: mButtonPosition does not match the size of mDoButton and mUndoButton!"
		, mButtonPosition == mDoButton->getPosition() && mButtonPosition == mUndoButton->getPosition()));

	sf::FloatRect buttonRect;
	if (mDoState)
	{
		// ALW - The user could call GameButton::setSize directly and circumvent UndoUIElem's interface.
		assert(("ALW - Logic Error: mButtonSize does not match the size of mDoButton!", mButtonSize == mDoButton->getSize()));
		buttonRect = sf::FloatRect(mButtonPosition.x, mButtonPosition.y, mButtonSize.x, mButtonSize.y);
	}
	else
	{
		// ALW - The user could call GameButton::setSize directly and circumvent UndoUIElem's interface.
		assert(("ALW - Logic Error: mButtonSize does not match the size of mUndoButton!", mButtonSize == mUndoButton->getSize()));
		buttonRect = sf::FloatRect(mButtonPosition.x, mButtonPosition.y, mButtonSize.x, mButtonSize.y);
	}

	sf::Transform combinedTransform = getTransform() * transform;
	buttonRect = combinedTransform.transformRect(buttonRect);

	mMouseOver = false;
	if (buttonRect.contains(mousePosition))
	{
		mMouseOver = true;
	}

	mContainer.handler(window, view, combinedTransform);
}

void UndoUIElem::handleEvent(const trmb::Event& gameEvent)
{
	// ALW - ButtonContainer still manages all event handling for its buttons. However, UndoUIElem needs to know when
	// ALW - the UI elem was clicked, so it can hide the appropriate button (by resizing it).
	if (mLeftClickPress == gameEvent.getType())
	{
		if (mMouseOver)
		{
			// ALW - It's not important which button was pressed, but just that a button was pressed.
			mPressed = true;
		}
	}
	else if (mLeftClickRelease == gameEvent.getType())
	{
		if (mPressed)
		{
			mPressed = false;

			if (mMouseOver)
			{
				toggleHandler();
			}
		}
	}
}

void UndoUIElem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mContainer, states);
}

void UndoUIElem::standardizeCharacterSize()
{
	// ALW - Set text and size for both buttons
	mDoButton->setSize(mButtonSize);
	mDoButton->setText(mDoText);
	mUndoButton->setSize(mButtonSize);
	mUndoButton->setText(mUndoText);

	// ALW - Standardize text
	mContainer.standardizeCharacterSize();

	// Rehide button based on mDoState
	const sf::Vector2f hide = sf::Vector2f(0.0f, 0.0f);

	if (mDoState)
	{
		mUndoButton->setSize(hide, false);
		mUndoButton->setText("", false);
	}
	else
	{
		mDoButton->setSize(hide, false);
		mDoButton->setText("", false);
	}
}

void UndoUIElem::toggleHandler()
{
	mDoState = !mDoState;
	const sf::Vector2f hide = sf::Vector2f(0.0f, 0.0f);

	if (mDoState)
	{
		mDoButton->setSize(mButtonSize, false);
		mDoButton->setText(mDoText, false);

		mUndoButton->setSize(hide, false);
		mUndoButton->setText("", false);
	}
	else
	{
		mDoButton->setSize(hide, false);
		mDoButton->setText("", false);

		mUndoButton->setSize(mButtonSize, false);
		mUndoButton->setText(mUndoText, false);
	}
}

void centerOrigin(UndoUIElem& uiElem, bool centerXAxis, bool centerYAxis)
{
	sf::Vector2f size = uiElem.getSize();
	float xAxis = 0.0f;
	float yAxis = 0.0f;

	if (centerXAxis)
		xAxis = std::floor(size.x / 2.0f);

	if (centerYAxis)
		yAxis = std::floor(size.y / 2.0f);

	uiElem.setOrigin(xAxis, yAxis);
}

} // namespace trmb
