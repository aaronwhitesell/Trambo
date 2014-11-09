#include "../../../../Include/Trambo/HUD/tabContainer.h"
#include "../../../../Include/Trambo/HUD/gameTab.h"
#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <algorithm>


namespace trmb
{

TabContainer::TabContainer(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& parentTransform
	, EventGuid leftClickPress)
: mWindow(window)
, mView(view)
, mParentTransform(parentTransform)
, mLeftClickPress(leftClickPress)
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

void TabContainer::handleEvent(const Event& gameEvent)
{
	if (mLeftClickPress == gameEvent.getType())
	{
		sf::Transform combinedTransform = getTransform() * mParentTransform;
		std::size_t index = 0;

		for (auto tab : mTabs)
		{
			// ALW - Keep the GameTab::mMouseOver var up-to-date.
			tab->handler(mWindow, mView, combinedTransform);

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

void TabContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto tab : mTabs)
	{
		target.draw(*tab, states);
	}
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
