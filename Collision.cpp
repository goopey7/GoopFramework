//Copyright Sam Collier 2022

#include "Collision.h"

bool Collision::checkBoundingBox(Actor* a1, Actor* a2)
{
	sf::Vector2f pos1 = a1->getWorldPosition();
	sf::Vector2f pos2 = a2->getWorldPosition();
	if (pos1.x + a1->getCollisionBox().left + a1->getCollisionBox().width < pos2.x + a2->getCollisionBox().left)
		return false;
	if (pos1.x + a1->getCollisionBox().left > pos2.x + a2->getCollisionBox().left + a2->getCollisionBox().width)
		return false;
	if (pos1.y + a1->getCollisionBox().top + a1->getCollisionBox().height < pos2.y + a2->getCollisionBox().top)
		return false;
	if (pos1.y + a1->getCollisionBox().top > pos2.y + a2->getCollisionBox().top + a2->getCollisionBox().height)
		return false;
	return true;
}

