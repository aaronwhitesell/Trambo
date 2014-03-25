#ifndef TRAMBO_LABEL_H
#define TRAMBO_LABEL_H

#include "component.h"
#include "../Resources/resourceHolder.h"

#include <SFML/Graphics/Text.hpp>

#include <memory>
#include <string>

namespace sf
{
	class Event;
	class RenderStates;
	class Rendertarget;
}

namespace Fonts
{
	enum class ID;
}

namespace trmb
{

class Label : public Component
{
public:
	typedef std::shared_ptr<Label> Ptr;


public:
						Label(const std::string& text, Fonts::ID font, const FontHolder& fonts);
	
	virtual bool		isSelectable() const;
	void				setText(const std::string& text);

	virtual void		handleEvent(const sf::Event& event);


private:
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Text			mText;
};

} // trmb namespace

#endif
