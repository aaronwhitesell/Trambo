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
	using Ptr = std::shared_ptr<GameButton>;


public:
							ButtonContainer(const sf::RenderWindow& window, const sf::View& view, const sf::Transform& parentTransform
								, EventGuid leftClickPress, EventGuid leftClickRelease);
							ButtonContainer(const ButtonContainer&) = delete;
	ButtonContainer&		operator=(const ButtonContainer&) = delete;

	int						getSize() const;
	Rects					getRects() const;

	void					handler();
	virtual void			handleEvent(const trmb::Event& gameEvent) override final;
	void					pack(Ptr button);


private:
	using Vector = std::vector<Ptr>;


private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void					standardizeCharacterSize();
	void					select(std::size_t index);
	bool					hasSelection() const;

	void					selectionHandler();


private:
	const sf::RenderWindow& mWindow;
	const sf::View&         mView;
	const sf::Transform&    mParentTransform;
	const EventGuid			mLeftClickPress;    // ALW - Matches the GUID in the Controller class.
	const EventGuid			mLeftClickRelease;  // ALW - Matches the GUID in the Controller class.
	Vector					mButtons;
	Rects					mRects;
	int						mSelectedButton;
};

} // namespace trmb

#endif
