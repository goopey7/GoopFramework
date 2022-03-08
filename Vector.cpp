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

