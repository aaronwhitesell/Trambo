#ifndef TRAMBO_SPRITE_NODE_H
#define TRAMBO_SPRITE_NODE_H

#include "sceneNode.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>


namespace sf
{
	class RenderStates;
	class RenderTarget;
}

namespace trmb
{

class SpriteNode : public SceneNode
{
public:
	explicit			SpriteNode(const sf::Texture &texture);
						SpriteNode(const sf::Texture &texture, const sf::IntRect &textureRect);
						SpriteNode(const SpriteNode &) = delete;
	SpriteNode &		operator=(const SpriteNode &) = delete;

private:
	virtual void		drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;


private:
	sf::Sprite			mSprite;
};

} // namespace trmb

#endif