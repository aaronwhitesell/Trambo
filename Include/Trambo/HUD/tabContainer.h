#ifndef TRAMBO_TAB_CONTAINER_H
#define TRAMBO_TAB_CONTAINER_H

#include "../Events/eventHandler.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>


namespace sf
{
	class Color;
	class RenderStates;
	class RenderTarget;
	class RenderWindow;
	class Transform;
	class View;
}

namespace trmb
{

class Event;
class GameTab;

class TabContainer : public sf::Transformable, public sf::Drawable, public trmb::EventHandler
{
public:
	using EventGuid = unsigned long;
	using Rects = std::vector <sf::FloatRect>;
	using Ptr = std::shared_ptr<GameTab>;


public:
							TabContainer(EventGuid leftClickPress);
							TabContainer(const TabContainer&) = delete;
	TabContainer&			operator=(const TabContainer&) = delete;

	int						getSize() const;
	Rects					getRects() const;

	void					setVisualScheme(sf::Color backgroundColor, sf::Color textColor, sf::Color outlineColor,
								sf::Color depressBackgroundColor, sf::Color depressTextColor, sf::Color depressOutlineColor,
								sf::Color disableBackgroundColor, sf::Color disableTextColor, sf::Color disableOutlineColor,
								float outLineThickness);

	void					handler(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& transform);
	virtual void			handleEvent(const trmb::Event& gameEvent) override final;
	void					pack(Ptr ptr);
	void					standardizeCharacterSize();
	void					deactivate();
	void					enable();
	void					disable();


private:
	using Vector = std::vector<Ptr>;


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void					activate(std::size_t index);
	bool					isActivated() const;


private:
	const EventGuid			mLeftClickPress;    // ALW - Matches the GUID in the Controller class.
	Vector					mTabs;
	Rects					mRects;
	int						mActivatedTab;
};

} // namespace trmb

#endif
