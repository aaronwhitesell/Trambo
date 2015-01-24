#include "../../../../Include/Trambo/HUD/GameButton.h"
#include "../../../../Include/Trambo/Events/event.h"
#include "../../../../Include/Trambo/Sounds/soundPlayer.h"
#include "../../../../Include/Trambo/Utilities/utility.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>


namespace trmb
{

GameButton::GameButton(Fonts::ID fontID, FontHolder& fonts, SoundEffects::ID soundID, SoundPlayer& sounds, sf::Vector2f size)
: mFonts(fonts)
, mSoundID(soundID)
, mSounds(sounds)
, mBackgroundColor(sf::Color(0u, 51u, 102u, 255u))
, mTextColor(sf::Color(255u, 255u, 255u, 255u))
, mOutlineColor(sf::Color(0u, 0u, 0u, 255u))
, mHoverBackgroundColor(sf::Color(0u, 76u, 153u, 255u))
, mHoverTextColor(sf::Color(255u, 255u, 255u, 255u))
, mHoverOutlineColor(sf::Color(0u, 0u, 0u, 255u))
, mDepressBackgroundColor(sf::Color(0u, 25u, 51u, 255u))
, mDepressTextColor(sf::Color(255u, 255u, 255u, 255u))
, mDepressOutlineColor(sf::Color(0u, 0u, 0u, 255u))
, mDisable(false)
, mDisableColorSchemeActive(false)
, mDisableBackgroundColor(sf::Color(160u, 160u, 160u, 255u))
, mDisableTextColor(sf::Color(224u, 224u, 224u, 255u))
, mDisableOutlineColor(sf::Color(128u, 128u, 128u, 255u))
, mMouseOver(false)
, mSelected(false)
, mPressed(false)
, mRestoreBackgroundSize(sf::Vector2f(0.0f, 0.0f))
, mRestoreCharacterSize(0)
{
	setSize(size);
	setFont(fontID);
	setCharacterSize(14);

	mBackground.setFillColor(mBackgroundColor);
	mBackground.setOutlineThickness(1.0f);
	mBackground.setOutlineColor(mOutlineColor);
}

bool GameButton::isMouseOver() const
{
	return mMouseOver;
}

bool GameButton::isSelected() const
{
	return mSelected;
}

bool GameButton::isPressed() const
{
	return mPressed;
}

bool GameButton::isDisabled() const
{
	return mDisable;
}

sf::Vector2f GameButton::getSize() const
{
	return mBackground.getSize();
}

unsigned int GameButton::getCharacterSize() const
{
	return mText.getCharacterSize();
}

void GameButton::setSize(sf::Vector2f size, bool resize)
{
	mBackground.setSize(size);

	if (resize)
		resizeFont();
}

void GameButton::setText(std::string string, bool resize)
{
	mText.setString(string);

	if (resize)
		resizeFont();
}

void GameButton::setFont(Fonts::ID fontID)
{
	mText.setFont(mFonts.get(fontID));
	resizeFont();
}

void GameButton::setCharacterSize(unsigned int characterSize, bool recenter)
{
	mText.setCharacterSize(characterSize);

	if (recenter)
		recenterText();
}

void GameButton::setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
	, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
	, sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
	, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
	, float outLineThickness)
{
	setBackgroundColor(backgroundColor);
	setTextColor(textColor);
	setOutlineColor(outlineColor);

	setHoverBackgroundColor(hoverBackgroundColor);
	setHoverTextColor(hoverTextColor);
	setHoverOutlineColor(hoverOutlineColor);

	setDepressBackgroundColor(depressBackgroundColor);
	setDepressTextColor(depressTextColor);
	setDepressOutlineColor(depressOutlineColor);

	setDisableBackgroundColor(disableBackgroundColor);
	setDisableTextColor(disableTextColor);
	setDisableOutlineColor(disableOutlineColor);

	setOutlineThickness(outLineThickness);
}

void GameButton::setOutlineThickness(float thickness)
{
	mBackground.setOutlineThickness(thickness);
}

void GameButton::setBackgroundColor(const sf::Color& color)
{
	mBackgroundColor = color;
	mBackground.setFillColor(color);
}

void GameButton::setTextColor(const sf::Color& color)
{
	mTextColor = color;
	mText.setColor(color);
}

void GameButton::setOutlineColor(const sf::Color& color)
{
	mOutlineColor = color;
	mBackground.setOutlineColor(color);
}

void GameButton::setHoverBackgroundColor(const sf::Color& color)
{
	mHoverBackgroundColor = color;
}

void GameButton::setHoverTextColor(const sf::Color& color)
{
	mHoverTextColor = color;
}

void GameButton::setHoverOutlineColor(const sf::Color& color)
{
	mHoverOutlineColor = color;
}

void GameButton::setDepressBackgroundColor(const sf::Color& color)
{
	mDepressBackgroundColor = color;
}

void GameButton::setDepressTextColor(const sf::Color& color)
{
	mDepressTextColor = color;
}

void GameButton::setDepressOutlineColor(const sf::Color& color)
{
	mDisableOutlineColor = color;
}

void GameButton::setDisableBackgroundColor(const sf::Color& color)
{
	mDisableBackgroundColor = color;
}

void GameButton::setDisableTextColor(const sf::Color& color)
{
	mDisableTextColor = color;
}

void GameButton::setDisableOutlineColor(const sf::Color& color)
{
	mDisableOutlineColor = color;
}

void GameButton::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void GameButton::select()
{
	if (!mDisable)
	{
		mSelected = true;

		mText.setColor(mHoverTextColor);
		mBackground.setFillColor(mHoverBackgroundColor);
		mBackground.setOutlineColor(mHoverOutlineColor);
	}
}

void GameButton::deselect()
{
	if (!mDisable)
	{
		mSelected = false;

		mText.setColor(mTextColor);
		mBackground.setFillColor(mBackgroundColor);
		mBackground.setOutlineColor(mOutlineColor);
	}
}

void GameButton::press()
{
	if (!mDisable)
	{
		mPressed = true;

		mText.setColor(mDepressTextColor);
		mBackground.setFillColor(mDepressBackgroundColor);
		mBackground.setOutlineColor(mDepressOutlineColor);
	}
}

void GameButton::cancelPress()
{
	if (!mDisable)
	{
		mPressed = false;

		deselect();
	}
}

void GameButton::activate()
{
	if (!mDisable)
	{
		mPressed = false;

		if (isSelected())
		{
			mText.setColor(mHoverTextColor);
			mBackground.setFillColor(mHoverBackgroundColor);
			mBackground.setOutlineColor(mHoverOutlineColor);
		}
		else
		{
			mText.setColor(mTextColor);
			mBackground.setFillColor(mBackgroundColor);
			mBackground.setOutlineColor(mOutlineColor);
		}

		mSounds.play(mSoundID);

		if (mCallback)
			mCallback();
	}
}

void GameButton::enable()
{
	mDisable = false;

	if (mDisableColorSchemeActive)
	{
		mText.setColor(mTextColor);
		mBackground.setFillColor(mBackgroundColor);
		mBackground.setOutlineColor(mOutlineColor);

		mDisableColorSchemeActive = false;
	}
}

void GameButton::disable(bool useDisableColorScheme)
{
	mDisable = true;
	mMouseOver = false;
	mSelected = false;
	mPressed = false;

	if (useDisableColorScheme)
	{
		mText.setColor(mDisableTextColor);
		mBackground.setFillColor(mDisableBackgroundColor);
		mBackground.setOutlineColor(mDisableOutlineColor);

		mDisableColorSchemeActive = true;
	}
}

void GameButton::unhide()
{
	setSize(mRestoreBackgroundSize, false);
	setCharacterSize(mRestoreCharacterSize, false);
}

void GameButton::hide()
{
	// ALW - hide() must be called before unhide(), so the restore values are assigned.
	mRestoreBackgroundSize = mBackground.getSize();
	const sf::Vector2f hideBackground = sf::Vector2f(0.0f, 0.0f);
	setSize(hideBackground, false);

	mRestoreCharacterSize = mText.getCharacterSize();
	const unsigned int hideText = 0;
	setCharacterSize(hideText, false);
}

void GameButton::handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform)
{
	mMouseOver = false;

	if (!mDisable)
	{
		const sf::Vector2i relativeToWindow = sf::Mouse::getPosition(window);
		const sf::Vector2f relativeToWorld = window.mapPixelToCoords(relativeToWindow, view);
		const sf::Vector2f mousePosition = relativeToWorld;

		sf::FloatRect buttonRect(getPosition().x, getPosition().y, mBackground.getSize().x, mBackground.getSize().y);
		buttonRect = transform.transformRect(buttonRect);

		if (buttonRect.contains(mousePosition))
		{
			mMouseOver = true;
		}
	}
}

void GameButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBackground, states);
	target.draw(mText, states);
}

void GameButton::recenterText()
{
	centerOrigin(mText);
	mText.setPosition(std::floor(mBackground.getSize().x / 2.0f), std::floor(mBackground.getSize().y / 2.0f));
}

void GameButton::resizeFont()
{
	// ALW - The text width is approximately 3/4 of the button width and the text
	// ALW - height is approximately the button height minus the vertical buffer.
	const float verticalBuffer = 10.0f;

	float width34 = mBackground.getSize().x / 4 * 3;
	float height10 = mBackground.getSize().y - verticalBuffer;
	std::string str = mText.getString();

	if (mBackground.getSize().x > 0 && mBackground.getSize().y > 0 && mText.getString() != "")
	{
		if (mText.getGlobalBounds().width < mBackground.getSize().x / 4 * 3 && mText.getGlobalBounds().height < mBackground.getSize().y - verticalBuffer)
		{
			while (mText.getGlobalBounds().width < mBackground.getSize().x / 4 * 3 && mText.getGlobalBounds().height < mBackground.getSize().y - verticalBuffer)
			{
				// ALW - If both the text width and height are less than the button size then increase the character size
				mText.setCharacterSize(mText.getCharacterSize() + 1);
			}
			if (mText.getGlobalBounds().width > mBackground.getSize().x / 4 * 3 || mText.getGlobalBounds().height > mBackground.getSize().y - verticalBuffer)
			{
				// ALW - If either the text width or height is larger than the button size then decrease the character size
				mText.setCharacterSize(mText.getCharacterSize() - 1);
			}
		}
		else
		{
			while (mText.getGlobalBounds().width > mBackground.getSize().x / 4 * 3 || mText.getGlobalBounds().height > mBackground.getSize().y - verticalBuffer)
			{
				// ALW - If the text width or height is larger than the button size then decrease the character size
				mText.setCharacterSize(mText.getCharacterSize() - 1);
			}
		}

		recenterText();
	}
}

} // namespace trmb
