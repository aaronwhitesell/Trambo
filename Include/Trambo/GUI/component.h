#ifndef TRAMBO_COMPONENT_H
#define TRAMBO_COMPONENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace trmb
{

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::shared_ptr<Component> Ptr;


public:
						Component();
	virtual				~Component();

	virtual bool		isSelectable() const = 0;

	bool				isSelected() const;
	bool                isPressed() const;
	virtual bool		isActive() const;

	virtual void		select();
	virtual	void		deselect();
	virtual void        press();
    virtual void        cancelPress();
	virtual void		activate();
	virtual void		deactivate();

	virtual bool		isIntersect(sf::Vector2i cursorPosition) const;
	virtual void		handleEvent(const sf::Event& event) = 0;


private:
	bool				mIsSelected;	// ALW - Refers to the selected state of a button.
	bool				mIsPressed;     // ALW - Refers to the pressed state of a button.
	bool				mIsActive;		// ALW - Refers to the released state of a button.
};

} // trmb namespace

#endif
