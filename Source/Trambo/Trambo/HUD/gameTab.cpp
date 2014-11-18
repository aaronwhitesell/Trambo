#include "../../../../Include/Trambo/HUD/GameTab.h"
#include "../../../../Include/Trambo/Events/event.h"
#include "../../../../Include/Trambo/Sounds/soundPlayer.h"
#include "../../../../Include/Trambo/Utilities/utility.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>


namespace trmb
{

GameTab::GameTab(Fonts::ID fontID, FontHolder& fonts, SoundEffects::ID soundID, SoundPlayer& sounds, sf::Vector2f size)
: mFonts(fonts)
, mSoundID(soundID)
, mSounds(sounds)
, mBackgroundColor(sf::Color(0u, 51u, 102u, 255u))
, mTextColor(sf::Color(255u, 255u, 255u, 255u))
, mOutlineColor(sf::Color(0u, 0u, 0u, 255u))
, mDepressBackgroundColor(sf::Color(0u, 25u, 51u, 255u))
, mDepressTextColor(sf::Color(255u, 255u, 255u, 255u))
, mDepressOutlineColor(sf::Color(0u, 0u, 0u, 255u))
, mDisable(false)
, mDisableBackgroundColor(sf::Color(160u, 160u, 160u, 255u))
, mDisableTextColor(sf::Color(224u, 224u, 224u, 255u))
, mDisableOutlineColor(sf::Color(128u, 128u, 128u, 255u))
, mMouseOver(false)
, mActivated(false)
{
	setSize(size);
	setFont(fontID);
	setCharacterSize(14);

	mBackground.setFillColor(mBackgroundColor);
	mBackground.setOutlineThickness(1.0f);
	mBackground.setOutlineColor(mOutlineColor);
}

bool GameTab::isMouseOver() const
{
	return mMouseOver;
}

bool GameTab::isActivated() const
{
	return mActivated;
}

sf::Vector2f GameTab::getSize() const
{
	return mSize;
}

unsigned int GameTab::getCharacerSize() const
{
	return mText.getCharacterSize();
}

void GameTab::setSize(sf::Vector2f size, bool resize)
{
	mSize = size;
	mBackground.setSize(mSize);
	resizeFont();

	if (resize)
		resizeFont();
}

void GameTab::setText(std::string string, bool resize)
{
	mText.setString(string);
	resizeFont();

	if (resize)
		resizeFont();
}

void GameTab::setFont(Fonts::ID fontID)
{
	mText.setFont(mFonts.get(fontID));
	resizeFont();
}

void GameTab::setCharacterSize(unsigned int characterSize)
{
	mText.setCharacterSize(characterSize);
	recenter();
}

void GameTab::setOutlineThickness(float thickness)
{
	mBackground.setOutlineThickness(thickness);
}

void GameTab::setBackgroundColor(const sf::Color& color)
{
	mBackgroundColor = color;
	mBackground.setFillColor(color);
}

void GameTab::setTextColor(const sf::Color& color)
{
	mTextColor = color;
	mText.setColor(color);
}

void GameTab::setOutlineColor(const sf::Color& color)
{
	mOutlineColor = color;
	mBackground.setOutlineColor(color);
}

void GameTab::setDepressBackgroundColor(const sf::Color& color)
{
	mDepressBackgroundColor = color;
}

void GameTab::setDepressTextColor(const sf::Color& color)
{
	mDepressTextColor = color;
}

void GameTab::setDepressOutlineColor(const sf::Color& color)
{
	mDisableOutlineColor = color;
}

void GameTab::setDisable(bool flag)
{
	mDisable = flag;
}

void GameTab::setDisableBackgroundColor(const sf::Color& color)
{
	mDisableBackgroundColor = color;
}

void GameTab::setDisableTextColor(const sf::Color& color)
{
	mDisableTextColor = color;
}

void GameTab::setDisableOutlineColor(const sf::Color& color)
{
	mDisableOutlineColor = color;
}

void GameTab::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void GameTab::activate()
{
	mActivated = true;

	if (mCallback)
		mCallback();


	mText.setColor(mDepressTextColor);
	mBackground.setFillColor(mDepressBackgroundColor);
	mBackground.setOutlineColor(mDepressOutlineColor);

	mSounds.play(mSoundID);
}

void GameTab::deactivate()
{
	mActivated = false;

	mText.setColor(mTextColor);
	mBackground.setFillColor(mBackgroundColor);
	mBackground.setOutlineColor(mOutlineColor);
}

void GameTab::handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform)
{
	const sf::Vector2i relativeToWindow = sf::Mouse::getPosition(window);
	const sf::Vector2f relativeToWorld = window.mapPixelToCoords(relativeToWindow, view);
	const sf::Vector2f mousePosition = relativeToWorld;

	sf::FloatRect tabRect(getPosition().x, getPosition().y, mSize.x, mSize.y);
	tabRect = transform.transformRect(tabRect);

	mMouseOver = false;
	if (tabRect.contains(mousePosition))
	{
		mMouseOver = true;
	}
}

void GameTab::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBackground, states);
	target.draw(mText, states);
}

void GameTab::recenter()
{
	centerOrigin(mText);
	mText.setPosition(std::floor(mSize.x / 2.0f), std::floor(mSize.y / 2.0f));
}

void GameTab::resizeFont()
{
	// ALW - The text width is approximately 3/4 of the tab width and the text
	// ALW - height is approximately the tab height minus the vertical buffer.
	const float verticalBuffer = 10.0f;

	float width34 = mSize.x / 4 * 3;
	float height10 = mSize.y - verticalBuffer;
	std::string str = mText.getString();

	if (mSize.x > 0 && mSize.y > 0 && mText.getString() != "")
	{
		if (mText.getGlobalBounds().width < mSize.x / 4 * 3 && mText.getGlobalBounds().height < mSize.y - verticalBuffer)
		{
			while (mText.getGlobalBounds().width < mSize.x / 4 * 3 && mText.getGlobalBounds().height < mSize.y - verticalBuffer)
			{
				// ALW - If both the text width and height are less than the tab size then increase the character size
				mText.setCharacterSize(mText.getCharacterSize() + 1);
			}
			if (mText.getGlobalBounds().width > mSize.x / 4 * 3 || mText.getGlobalBounds().height > mSize.y - verticalBuffer)
			{
				// ALW - If either the text width or height is larger than the tab size then decrease the character size
				mText.setCharacterSize(mText.getCharacterSize() - 1);
			}
		}
		else
		{
			while (mText.getGlobalBounds().width > mSize.x / 4 * 3 || mText.getGlobalBounds().height > mSize.y - verticalBuffer)
			{
				// ALW - If the text width or height is larger than the tab size then decrease the character size
				mText.setCharacterSize(mText.getCharacterSize() - 1);
			}
		}

		recenter();
	}
}

} // namespace trmb
