//Copyright Sam Collier 2022

#include "Collision.h"

void Collision::checkBoundingBox(Actor* a1, Actor* a2)
{
	sf::Vector2f pos1 = a1->getWorldPosition();
	sf::Vector2f pos2 = a2->getWorldPosition();
	if (pos1.x + a1->getCollisionBox().left + a1->getCollisionBox().width < pos2.x + a2->getCollisionBox().left)
		return;
	if (pos1.x + a1->getCollisionBox().left > pos2.x + a2->getCollisionBox().left + a2->getCollisionBox().width)
		return;
	if (pos1.y + a1->getCollisionBox().top + a1->getCollisionBox().height < pos2.y + a2->getCollisionBox().top)
		return;
	if (pos1.y + a1->getCollisionBox().top > pos2.y + a2->getCollisionBox().top + a2->getCollisionBox().height)
		return;
	unsigned int a1Sides = 0;
	unsigned int a2Sides = 0;

	if(pos1.x + a1->getCollisionBox().left + a1->getCollisionBox().width < pos2.x + a2->getCollisionBox().left + a2->getCollisionBox().width)
	{
		a1Sides |= gf::Side::Right;
		a2Sides |= gf::Side::Left;
	}
	if(pos1.x + a1->getCollisionBox().left > pos2.x + a2->getCollisionBox().left)
	{
		a1Sides |= gf::Side::Left;
		a2Sides |= gf::Side::Right;
	}
	a1->onCollision(a2, a1Sides);
	a2->onCollision(a1, a2Sides);
	return;
}

