#include "../../../../Include/Trambo/SceneNodes/spriteNode.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace trmb
{

SpriteNode::SpriteNode(const sf::Texture &texture)
: mSprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &textureRect)
: mSprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

} // namespace trmb
