#include "../../../../Include/Trambo/HUD/buttonContainer.h"
#include "../../../../Include/Trambo/HUD/gameButton.h"
#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/View.hpp>

#include <algorithm>


namespace trmb
{

ButtonContainer::ButtonContainer(EventGuid leftClickPress, EventGuid leftClickRelease)
: mLeftClickPress(leftClickPress)
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

void ButtonContainer::setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor
		, sf::Color hoverBackgroundColor, sf::Color hoverTextColor, sf::Color hoverOutlineColor
		, sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor
		, sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor
		, float outLineThickness)
{
	for (auto button : mButtons)
	{
		button->setBackgroundColor(backgroundColor);
		button->setTextColor(textColor);
		button->setOutlineColor(outlineColor);

		button->setHoverBackgroundColor(hoverBackgroundColor);
		button->setHoverTextColor(hoverTextColor);
		button->setHoverOutlineColor(hoverOutlineColor);

		button->setDepressBackgroundColor(depressBackgroundColor);
		button->setDepressTextColor(depressTextColor);
		button->setDepressOutlineColor(depressOutlineColor);

		button->setDisableBackgroundColor(disableBackgroundColor);
		button->setDisableTextColor(disableTextColor);
		button->setDisableOutlineColor(disableOutlineColor);

		button->setOutlineThickness(outLineThickness);
	}
}

void ButtonContainer::handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform)
{
	// ALW - This should occur on a mouse moved event. Otherwise, the position of the mouse is checked every frame!
	sf::Transform combinedTransform = getTransform() * transform;

	for (auto button : mButtons)
	{
		button->handler(window, view, combinedTransform);
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

void ButtonContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto button : mButtons)
	{
		target.draw(*button, states);
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
