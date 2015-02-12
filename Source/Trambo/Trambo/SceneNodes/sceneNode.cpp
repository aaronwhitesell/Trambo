#include "../../../../Include/Trambo/SceneNodes/sceneNode.h"
#include "../../../../Include/Trambo/Utilities/utility.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include <algorithm>
#include <cassert>
#include <functional>


namespace trmb
{

SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), 
		[&] (Ptr &p) 
		{ 
			return p.get() == &node; 
		});

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode *node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::checkSceneCollision(SceneNode &sceneGraph, std::set<Pair> &collisionPairs, bool preserveOrder)
{
	checkNodeCollision(sceneGraph, collisionPairs, preserveOrder);

	for (Ptr &child : sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs, preserveOrder);
}

void SceneNode::checkNodeCollision(SceneNode &node, std::set<Pair> &collisionPairs, bool preserveOrder)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
	{
		if (preserveOrder)
		{
			// ALW - This is useful when one unique layer is compared against another unique layer.
			// ALW - The benefit is that when layer 1 is compared against layer 2 the pairs will
			// ALW - always be in the same order (layer 1, layer 2).
			collisionPairs.insert(Pair(this, &node));
		}
		else
		{
			// ALW - This is useful when a scenegraph compares itself. There will be duplicate collisions,
			// ALW - but in reverse order. By using std::minmax all pairs will be of the same order and
			// ALW - duplicates will not be inserted (elements of a set are unique).
			collisionPairs.insert(std::minmax(this, &node));
		}
	}

	for (Ptr &child : mChildren)
		child->checkNodeCollision(node, collisionPairs, preserveOrder);
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void SceneNode::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

bool SceneNode::isMarkedForRemoval() const
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	// By default, scene node does not need to be removed
	return false;
}

void SceneNode::updateCurrent(sf::Time)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr &child : mChildren)
		child->update(dt);
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);

	// Draw bounding rectangle - disable by default
//	drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const Ptr &child : mChildren)
		child->draw(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget &target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

bool collision(const SceneNode &lhs, const SceneNode &rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float distance(const SceneNode &lhs, const SceneNode &rhs)
{
	return trmb::length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

} // namespace trmb
