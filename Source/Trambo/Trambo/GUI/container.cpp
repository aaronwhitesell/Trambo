#include "../../../../Include/Trambo/GUI/container.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


namespace trmb
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
}

Container::Container(sf::RenderWindow* window)
: mChildren()
, mSelectedChild(-1)
, mWindow(window)
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);

	// ALW - If no Component is selected and Component is selectable then select it.
	if (!hasSelection() && component->isSelectable())
		select(mChildren.size() - 1);

	// ALW - Hack - Fake a MouseMoved event to force an update. The cursor may be over a button, but hasn't moved.
	sf::Event event;
	event.type = sf::Event::EventType::MouseMoved;
	handleEvent(event);
}

bool Container::isSelectable() const
{
	return false;
}

void Container::handleEvent(const sf::Event& event)
{
	// If we have selected a child then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				mChildren[mSelectedChild]->press();
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				mChildren[mSelectedChild]->activate();
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		int index = 0;
		for (const Component::Ptr& child : mChildren)
		{
			if (child->isSelectable())
			{
				const sf::Vector2i cursorPosition = sf::Mouse::getPosition(*mWindow);
				if (child->isIntersect(cursorPosition))
				{
					select(index);
					break;
				}
				else if (child->isPressed())
					child->cancelPress();
			}
			++index;
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (hasSelection())
			{
				const sf::Vector2i cursorPosition = sf::Mouse::getPosition(*mWindow);
				if (mChildren[mSelectedChild]->isIntersect(cursorPosition))
					mChildren[mSelectedChild]->press();
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (hasSelection() && mChildren[mSelectedChild]->isPressed())
			{
				const sf::Vector2i cursorPosition = sf::Mouse::getPosition(*mWindow);
				if (mChildren[mSelectedChild]->isIntersect(cursorPosition))
					mChildren[mSelectedChild]->activate();
			}
		}
	}

	// ALW - TODO - Joystick UI

}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const Component::Ptr& child : mChildren)
		target.draw(*child, states);
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable() && !mChildren[index]->isPressed())
	{
		if (hasSelection())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do
		next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());

	// Select that component
	select(prev);
}

} // trmb namespac
