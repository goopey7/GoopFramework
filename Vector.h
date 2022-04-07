//Copyright Sam Collier 2022
#pragma once

#include <SFML/System/Vector2.hpp>

class Vector
{
	public:
		static float size(sf::Vector2f v);
		static sf::Vector2f normalize(sf::Vector2f v);

		// divides member-wise v1/v2
		static sf::Vector2f divide(sf::Vector2f v1, sf::Vector2f v2);

		// multiply member-wise
		static sf::Vector2f multiply(sf::Vector2f v1, sf::Vector2f v2);
};

