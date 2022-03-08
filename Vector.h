//Copyright Sam Collier 2022
#pragma once

#include <SFML/System/Vector2.hpp>

class Vector
{
	public:
		static float size(sf::Vector2f v);
		static sf::Vector2f normalize(sf::Vector2f v);
};

