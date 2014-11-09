#include "../../../../Include/Trambo/HUD/buttonContainer.h"
#include "../../../../Include/Trambo/HUD/gameButton.h"
#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <algorithm>


namespace trmb
{

ButtonContainer::ButtonContainer(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& parentTransform
	, EventGuid leftClickPress, EventGuid leftClickRelease)
: mWindow(window)
, mView(view)
, mParentTransform(parentTransform)
, mLeftClickPress(leftClickPress)
, mLeftClickRelease(leftClickRelease)
, mSelectedButton(-1)
{
}

int ButtonContainer::getSize() const
{
	return mButtons.size();
}

ButtonContainer::Rects ButtonContainer::getRects() const
{
	Rects rects;
	const sf::Transform transform = getTransform();
	for (auto button : mButtons)
	{
		sf::Vector2f rectPosition = button->getPosition();
		sf::Vector2f rectSize = button->getSize();
		sf::FloatRect rect(rectPosition.x, rectPosition.y, rectSize.x, rectSize.y);

		rects.emplace_back(transform.transformRect(rect));
	}

	return rects;
}

void ButtonContainer::handler()
{
	// ALW - TODO - This should occur on a mouse moved event. Otherwise,
	// ALW - TODO - the position of the mouse is checked every frame!

	sf::Transform combinedTransform = getTransform() * mParentTransform;

	for (auto button : mButtons)
	{
		button->handler(mWindow, mView, combinedTransform);
	}

	selectionHandler();
}

void ButtonContainer::handleEvent(const Event& gameEvent)
{
	if (mLeftClickPress == gameEvent.getType())
	{
		if (hasSelection())
		{
			if (mButtons.at(mSelectedButton)->isMouseOver())
			{
				mButtons.at(mSelectedButton)->press();
			}
		}
	}
	else if (mLeftClickRelease == gameEvent.getType())
	{
		if (hasSelection() && mButtons.at(mSelectedButton)->isPressed())
		{
			if (mButtons.at(mSelectedButton)->isMouseOver())
			{
				mButtons.at(mSelectedButton)->activate();
			}
		}
	}
}

void ButtonContainer::pack(Ptr button)
{
	mButtons.emplace_back(button);
	standardizeCharacterSize();
}

void ButtonContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto button : mButtons)
	{
		target.draw(*button, states);
	}
}

void ButtonContainer::standardizeCharacterSize()
{
	std::vector<Ptr>::const_iterator iter = begin(mButtons);
	if (iter != end(mButtons))
	{
		unsigned int min = (*iter)->getCharacerSize();
		++iter;

		for (; iter != end(mButtons); ++iter)
		{
			// ALW - Find the smallest character size
			min = std::min(min, (*iter)->getCharacerSize());
		}

		for (auto button : mButtons)
		{
			// ALW - Apply smallest character size to all
			(button)->setCharacterSize(min);
		}
	}
}

void ButtonContainer::select(std::size_t index)
{
	if (!mButtons.at(index)->isPressed())
	{
		if (hasSelection())
		{
			mButtons.at(mSelectedButton)->deselect();
		}

		mButtons.at(index)->select();
		mSelectedButton = index;
	}
}

bool ButtonContainer::hasSelection() const
{
	return mSelectedButton >= 0;
}

void ButtonContainer::selectionHandler()
{
	int index = 0;
	bool hasSelection = false;
	for (auto button : mButtons)
	{
		if (button->isMouseOver())
		{
			// ALW - Mouse is over the button
			select(index);
			hasSelection = true;
			break;
		}
		else if (button->isPressed())
		{
			// ALW - Mouse is not over the button, and pressed
			button->cancelPress();
		}
		else
		{
			// ALW - Mouse is not over the button, and not pressed
			button->deselect();
		}

		++index;
	}

	// ALW - Is any button selected?
	if (!hasSelection)
		mSelectedButton = -1;
}

} // namespace trmb
