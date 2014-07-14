#ifndef TRAMBO_ENTITY_H
#define TRAMBO_ENTITY_H

#include "sceneNode.h"

#include <SFML/System/Vector2.hpp>


namespace sf
{
	Time;
}

namespace trmb
{

class Entity : public SceneNode
{
public:
						Entity();
	explicit			Entity(int hitpoints);

	void				setHitpoints(int hitpoints);
	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float vx, float vy);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	sf::Vector2f		getVelocity() const;

	int					getHitpoints() const;
	void				heal(int points);
	void				damage(int points);
	void				destroy();
	virtual void		remove();
	virtual bool		isDestroyed() const;


protected:
	virtual void		updateCurrent(sf::Time dt);


private:
	sf::Vector2f		mVelocity;
	int					mHitpoints;
};

} // namespace trmb

#endif
