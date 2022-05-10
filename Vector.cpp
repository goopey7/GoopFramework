//Copyright Sam Collier 2022

#include "Vector.h"
#include <cmath>

float Vector::size(sf::Vector2f v)
{
	return sqrtf(powf(v.x,2.f)+powf(v.y,2.f));
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

float Vector::angle(sf::Vector2f v1, sf::Vector2f v2)
{
	return acosf(dot(v1,v2)/(size(v1)*size(v2)));
}

float Vector::dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}

float Vector::distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return sqrtf(powf(v2.x-v1.x,2.f) + powf(v2.y-v1.y,2.f));
}

