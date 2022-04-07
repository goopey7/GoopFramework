//Copyright Sam Collier 2022
#pragma once

#include "Actor.h"
#include "Vector.h"

class Collision
{
	public:
		// returns true if point lies within Actor's aabb
		static bool ActorVPoint(const Actor* a, const sf::Vector2f point);

		// returns true if actors' aabbs are colliding
		static bool ActorVActor(const Actor* a1, const Actor* a2);

		// returns true if ray collides with actor's aabb
		static bool RayVsActor(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDir,
				const Actor* a,
				sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime);

		// moving rect vs static rect
		static bool MovingActorVActor(const Actor* mA, const Actor* sA,
				sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt);
};

