#include "../../../../Include/Trambo/GUI/component.h"


namespace trmb
{

Component::Component()
: mIsSelected(false)
, mIsPressed(false)
, mIsActive(false)
{
}

Component::~Component()
{
}

bool Component::isSelected() const
{
	return mIsSelected;
}

void Component::select()
{
	mIsSelected = true;
}

void Component::deselect()
{
	mIsSelected = false;
}

bool Component::isPressed() const
{
	return mIsPressed;
}

void Component::press()
{
	mIsPressed = true;
}

void Component::cancelPress()
{
	mIsPressed = false;
}

bool Component::isActive() const
{
	return mIsActive;
}

void Component::activate()
{
	mIsActive = true;
}

void Component::deactivate()
{
	mIsActive = false;
}

bool Component::isIntersect(sf::Vector2i cursorPosition) const
{
	return false;
}

} // trmb namespace
