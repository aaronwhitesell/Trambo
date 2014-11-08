#ifndef TRAMBO_BUTTON_CONTAINER_H
#define TRAMBO_BUTTON_CONTAINER_H

#include "../Events/eventHandler.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>


namespace sf
{
	class RenderStates;
	class RenderTarget;
	class RenderWindow;
	class View;
}

namespace trmb
{

class GameButton;

class ButtonContainer : public sf::Transformable, public sf::Drawable, public trmb::EventHandler
{
public:
	using EventGuid = unsigned long;
	using Rects = std::vector <sf::FloatRect>;
	using ButtonPtr = std::shared_ptr<GameButton>;
	using ButtonVector = std::vector<ButtonPtr>;


public:
							ButtonContainer(EventGuid leftClickPress, EventGuid leftClickRelease);
							ButtonContainer(const ButtonContainer&) = delete;
	ButtonContainer&		operator=(const ButtonContainer&) = delete;

	int						getSize() const;
	Rects					getRects() const;

	void					handler(const sf::RenderWindow &window, const sf::View& view, const sf::Transform& transform);
	virtual void			handleEvent(const trmb::Event& gameEvent) override final;
	void					pack(ButtonPtr button);


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void					standardizeCharacterSize();
	void					select(std::size_t index);
	bool					hasSelection() const;

	void					selectionHandler(void);


private:
	const EventGuid			mLeftClickPress;    // ALW - Matches the GUID in the Controller class.
	const EventGuid			mLeftClickRelease;  // ALW - Matches the GUID in the Controller class.
	ButtonVector			mButtons;
	Rects					mRects;
	int						mSelectedButton;
};

} // namespace trmb

#endif
