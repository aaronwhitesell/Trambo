#ifndef TRAMBO_BUTTON_H
#define TRAMBO_BUTTON_H

#include "component.h"
#include "../States/state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>
#include <memory>
#include <string>


namespace sf
{
	class Event;
	class RenderTarget;
	class RenderStates;
}

namespace Fonts
{
	enum class ID;
}

namespace SoundEffects
{
	enum class ID;
}

namespace Textures
{
	enum class ID;
}

namespace trmb 
{ 

class SoundPlayer;

class Button : public Component
{
public:
	typedef std::shared_ptr<Button>		Ptr;
	typedef std::function<void()>		Callback;

	enum class Type
	{
		Normal,
		Selected,
		Pressed,
		ButtonCount
	};

public:
							Button(State::Context context, Fonts::ID font, SoundEffects::ID soundEffect, Textures::ID texture, 
								int buttonWidth, int buttonHeight);
								
	void					setCallback(Callback callback);
	void					setText(const std::string& text);
	void					setToggle(bool flag);

	virtual bool			isSelectable() const;

	virtual void			select();
	virtual void			deselect();
    virtual void            press();
    virtual void            cancelPress();
	virtual void			activate();
	virtual void			deactivate();

	virtual bool			isIntersect(sf::Vector2i cursorPosition) const;
	virtual void			handleEvent(const sf::Event& event);


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					changeTexture(Type buttonType);

private:
	Callback				mCallback;
	sf::Sprite				mSprite;
	sf::Text				mText;
	bool					mIsToggle;			// The button remains pressed (active) until explicitly changed (supports poll method).
	SoundPlayer&			mSounds;
	SoundEffects::ID		mSoundEffect;
	int                     mButtonWidth;
	int                     mButtonHeight;
};

} // trmb namespace

#endif
