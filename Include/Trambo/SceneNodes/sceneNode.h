#ifndef TRAMBO_SCENE_NODE_H
#define TRAMBO_SCENE_NODE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <set>
#include <utility>
#include <vector>


namespace sf
{
	class Time;
	class RenderStates;
	class RenderTarget;
}

namespace trmb
{

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;


public:
							SceneNode();
							SceneNode(const SceneNode &) = delete;
	SceneNode &				operator=(const SceneNode &) = delete;

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode &node);

	void					update(sf::Time dt);

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;

	void					checkSceneCollision(SceneNode &sceneGraph, std::set<Pair> &collisionPairs, bool preserveOrder = false);
	void					checkNodeCollision(SceneNode &node, std::set<Pair> &collisionPairs, bool preserveOrder = false);
	void					removeWrecks();
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			isMarkedForRemoval() const;
	virtual bool			isDestroyed() const;


private:
	virtual void			updateCurrent(sf::Time dt);
	void					updateChildren(sf::Time dt);

	virtual void			draw(sf::RenderTarget &target, sf::RenderStates states) const final;
	virtual void			drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
	void					drawBoundingRect(sf::RenderTarget &target, sf::RenderStates states) const;


private:
	std::vector<Ptr>		mChildren;
	SceneNode*				mParent;
};

bool	collision(const SceneNode &lhs, const SceneNode &rhs);
float	distance(const SceneNode &lhs, const SceneNode &rhs);

} // namespace trmb

#endif
