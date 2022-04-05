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

bool Collision::ActorVActor(Actor* a1, Actor* a2)
{
	sf::FloatRect box1 = a1->getCollisionBox(), box2 = a2->getCollisionBox();
	sf::Vector2f pos1 = a1->getWorldPosition(), pos2 = a2->getWorldPosition();

	if (pos1.x + box1.width < pos2.x + box2.left)
	{
		return false;
	}
	if (pos1.x + box1.left > pos2.x + box2.width)
	{
		return false;
	}
	if (pos1.y + box1.height < pos2.y + box2.top)
	{
		return false;
	}
	if (pos1.y + box1.top > pos2.y + box2.height)
	{
		return false;
	}
	return true;
}

