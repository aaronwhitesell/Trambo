#ifndef TRAMBO_UTILITY_H
#define TRAMBO_UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

#include <iomanip>
#include <sstream>
#include <string>


namespace sf
{
	class RectangleShape;
	class RenderWindow;
	class Sprite;
	class Text;
}

namespace trmb
{

class Animation;

// Convert enumerators to strings
std::string		toString(sf::Keyboard::Key key);
std::string		toString(sf::Mouse::Button key);

// ALW - Same effect as std::to_string, but with precision control.
template <typename T>
std::string toStringWithPrecision(const T a_value, const int n)
{
	std::ostringstream out;
	out << std::setprecision(n) << a_value;
	return out.str();
}

// Call setOrigin() with the center of the object
void			centerOrigin(sf::Sprite& sprite, bool centerXAxis = true, bool centerYAxis = true);
void			centerOrigin(sf::Text& text, bool centerXAxis = true, bool centerYAxis = true);
void			centerOrigin(sf::RectangleShape& rectangleShape, bool centerXAxis = true, bool centerYAxis = true);
void			centerOrigin(Animation& animation, bool centerXAxis = true, bool centerYAxis = true);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

bool			isWindowFocused(const sf::RenderWindow &window);
} // trmb namespace

#endif
