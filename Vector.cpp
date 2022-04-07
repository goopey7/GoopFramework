//Copyright Sam Collier 2022

#include "Vector.h"
#include <cmath>

float Vector::size(sf::Vector2f v)
{
	return sqrtf(v.x*v.x+v.y*v.y);
}

sf::Vector2f Vector::normalize(sf::Vector2f v)
{
	return v / size(v);
}

sf::Vector2f Vector::divide(sf::Vector2f v1, sf::Vector2f v2)
{
	return sf::Vector2f(v1.x/v2.x,v1.y/v2.y);
}

sf::Vector2f Vector::multiply(sf::Vector2f v1, sf::Vector2f v2)
{
	return sf::Vector2f(v1.x*v2.x,v1.y*v2.y);
}

