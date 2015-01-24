#ifndef TRAMBO_GAME_BUTTON_H
#define TRAMBO_GAME_BUTTON_H

#include "../Resources/resourceHolder.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>


namespace sf
{
	class RenderStates;
	class RenderTarget;
	class RenderWindow;
	class Transform;
	class View;
}

namespace Fonts
{
	enum class ID;
}

namespace SoundEffects
{
	enum class ID;
}

namespace trmb
{

class SoundPlayer;

class GameButton : public sf::Transformable, public sf::Drawable
{
public:
	using Callback = std::function<void()>;


public:
							GameButton(Fonts::ID fontID, FontHolder& fonts, SoundEffects::ID soundID, SoundPlayer& sounds,
								sf::Vector2f size = sf::Vector2f(50.0f, 20.0f));
							GameButton(const GameButton&) = delete;
	GameButton&				operator=(const GameButton&) = delete;

	bool					isMouseOver() const;
	bool					isSelected() const;
	bool					isPressed() const;
	bool                    isDisabled() const;

	sf::Vector2f			getSize() const;
	unsigned int			getCharacterSize() const;

	void					setSize(sf::Vector2f size, bool resize = true);
	void					setText(std::string string, bool resize = true);
	void					setFont(Fonts::ID fontID);
	void					setCharacterSize(unsigned int CharacterSize, bool recenter = true);

	void					setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
								, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
								, sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
								, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
								, float outLineThickness);

	void					setOutlineThickness(float thickness);

	void					setBackgroundColor(const sf::Color& color);
	void					setTextColor(const sf::Color& color);
	void					setOutlineColor(const sf::Color& color);

	void					setHoverBackgroundColor(const sf::Color& color);
	void					setHoverTextColor(const sf::Color& color);
	void					setHoverOutlineColor(const sf::Color& color);

	void					setDepressBackgroundColor(const sf::Color& color);
	void					setDepressTextColor(const sf::Color& color);
	void					setDepressOutlineColor(const sf::Color& color);

	void					setDisableBackgroundColor(const sf::Color& color);
	void					setDisableTextColor(const sf::Color& color);
	void					setDisableOutlineColor(const sf::Color& color);

	void					setCallback(Callback callback);

	void					select();
	void					deselect();
	void					press();
	void					cancelPress();
	void					activate();

	void					enable();
	void					disable(bool useDisableColorScheme);
	void					unhide();
	void					hide();

	void					handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform);


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void					recenterText();
	void					resizeFont();


private:
	FontHolder&				mFonts;
	SoundEffects::ID		mSoundID;
	SoundPlayer&			mSounds;

	sf::RectangleShape		mBackground;
	sf::Text				mText;

	sf::Color				mBackgroundColor;
	sf::Color				mTextColor;
	sf::Color				mOutlineColor;

	sf::Color				mHoverBackgroundColor;
	sf::Color				mHoverTextColor;
	sf::Color				mHoverOutlineColor;

	sf::Color				mDepressBackgroundColor;
	sf::Color				mDepressTextColor;
	sf::Color				mDepressOutlineColor;

	bool					mDisable;
	bool					mDisableColorSchemeActive;
	sf::Color				mDisableBackgroundColor;
	sf::Color				mDisableTextColor;
	sf::Color				mDisableOutlineColor;

	Callback				mCallback;

	bool					mMouseOver;
	bool					mSelected;
	bool					mPressed;

	sf::Vector2f			mRestoreBackgroundSize;
	unsigned int			mRestoreCharacterSize;
};

} // namespace trmb

#endif
