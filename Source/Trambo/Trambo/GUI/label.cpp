#include "../../../../Include/Trambo/GUI/label.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>


namespace trmb
{

Label::Label(const std::string& text, Fonts::ID font, const FontHolder& fonts)
: mText(text, fonts.get(font), 16)
{
}

bool Label::isSelectable() const
{
	return false;
}

void Label::handleEvent(const sf::Event&)
{
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mText, states);
}

void Label::setText(const std::string& text)
{
	mText.setString(text);
}

} // trmb namespace
