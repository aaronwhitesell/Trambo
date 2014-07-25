#ifndef TRAMBO_CAMERA_H
#define TRAMBO_CAMERA_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>


namespace trmb
{

class Camera
{
public:
							Camera(const sf::View &view, sf::FloatRect worldBounds);
							Camera(const Camera &) = delete;
	Camera &				operator=(const Camera &) = delete;

	sf::View &				getView();
	sf::FloatRect			getViewBounds() const;

	void					update(sf::Vector2f position);


private:
	void					correctPosition();


private:
	sf::View				mView;
	sf::FloatRect			mWorldBounds;
};

} // trmb namespace

#endif
