#include "../../../../Include/Trambo/HUD/tabContainer.h"
#include "../../../../Include/Trambo/HUD/gameTab.h"
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

TabContainer::TabContainer(EventGuid leftClickPress)
: mLeftClickPress(leftClickPress)
, mActivatedTab(-1)
{
}

int TabContainer::getSize() const
{
	return mTabs.size();
}

TabContainer::Rects TabContainer::getRects() const
{
	Rects rects;
	const sf::Transform transform = getTransform();
	for (auto tab : mTabs)
	{
		sf::Vector2f rectPosition = tab->getPosition();
		sf::Vector2f rectSize = tab->getSize();
		sf::FloatRect rect(rectPosition.x, rectPosition.y, rectSize.x, rectSize.y);

		rects.emplace_back(transform.transformRect(rect));
	}

	return rects;
}

void TabContainer::setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor,
		sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor,
	    sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor,
		float outLineThickness)
{
	for (auto tab : mTabs)
	{
		tab->setBackgroundColor(backgroundColor);
		tab->setTextColor(textColor);
		tab->setOutlineColor(outlineColor);

		tab->setDepressBackgroundColor(depressBackgroundColor);
		tab->setDepressTextColor(depressTextColor);
		tab->setDepressOutlineColor(depressOutlineColor);

		tab->setDisableBackgroundColor(disableBackgroundColor);
		tab->setDisableTextColor(disableTextColor);
		tab->setDisableOutlineColor(disableOutlineColor);

		tab->setOutlineThickness(outLineThickness);
	}
}

void TabContainer::handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform)
{
	// ALW - This should occur on a left-click press event. Otherwise, the position of the mouse is checked every frame!
	// ALW - In addition to this the combined transform cannot be calculated in the ctor, because the object is unitialized
	// ALW - so the transform is unknown. Therefore, the handler function is used to pass in the parent transform.
	// ALW - Idealy, the transform would be passed directly to the handleEvent() method, but this is not possible.

	sf::Transform combinedTransform = getTransform() * transform;

	for (auto tab : mTabs)
	{
		tab->handler(window, view, combinedTransform);
	}
}

void TabContainer::handleEvent(const Event& gameEvent)
{
	if (mLeftClickPress == gameEvent.getType())
	{
		std::size_t index = 0;

		for (auto tab : mTabs)
		{
			if (tab->isMouseOver())
			{
				activate(index);
				break;
			}

			++index;
		}
	}
}

void TabContainer::pack(Ptr ptr)
{
	mTabs.emplace_back(ptr);
	standardizeCharacterSize();
}

void TabContainer::standardizeCharacterSize()
{
	std::vector<Ptr>::const_iterator iter = begin(mTabs);
	if (iter != end(mTabs))
	{
		unsigned int min = (*iter)->getCharacerSize();
		++iter;

		for (; iter != end(mTabs); ++iter)
		{
			// ALW - Find the smallest character size
			min = std::min(min, (*iter)->getCharacerSize());
		}

		for (auto tab : mTabs)
		{
			// ALW - Apply smallest character size to all
			(tab)->setCharacterSize(min);
		}
	}
}

void TabContainer::deactivate()
{
	// ALW - Leave no tab activated
	for (auto tab : mTabs)
	{
		if (tab->isActivated())
		{
			tab->deactivate();
		}
	}

	mActivatedTab = -1;
}

void TabContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto tab : mTabs)
	{
		target.draw(*tab, states);
	}
}

void TabContainer::activate(std::size_t index)
{
	if (index != mActivatedTab)
	{
		// ALW - A new tab has been activated
		if (isActivated())
		{
			// ALW - Unactivate the old tab
			mTabs.at(mActivatedTab)->deactivate();
		}

		mTabs.at(index)->activate();
		mActivatedTab = index;
	}
}

bool TabContainer::isActivated() const
{
	return mActivatedTab >= 0;
}

} // namespace trmb
