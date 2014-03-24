#ifndef TRAMBO_UTILITY_H
#define TRAMBO_UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>
#include <string>


namespace sf
{
	class Sprite;
	class Text;
}

namespace trmb
{

class Animation;

// Convert enumerators to strings
std::string		toString(sf::Keyboard::Key key);
std::string		toString(sf::Mouse::Button key);

// Call setOrigin() with the center of the object
void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);
void			centerOrigin(trmb::Animation& animation);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

} // trmb namespace

#endif
