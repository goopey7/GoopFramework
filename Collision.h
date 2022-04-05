//Copyright Sam Collier 2022
#pragma once

#include "Actor.h"

class Collision
{
	public:
		// returns true if point lies within Actor's aabb
		static bool ActorVPoint(Actor* a, const sf::Vector2f point);
};

