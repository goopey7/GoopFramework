//Copyright Sam Collier 2022

#include "Collision.h"

bool Collision::ActorVPoint(Actor* a, const sf::Vector2f point)
{
	sf::FloatRect box = a->getCollisionBox();
	sf::Vector2f aLocation = a->getWorldPosition();
	
	// does the point lie within the bounds of the box?
	return (point.x >= aLocation.x + box.left && point.x <= aLocation.x + box.width
			&& point.y >= aLocation.y + box.top && point.y <= aLocation.y + box.height);
}

