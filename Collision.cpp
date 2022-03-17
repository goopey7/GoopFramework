//Copyright Sam Collier 2022

#include "Collision.h"

void endCollision(Actor* a1, Actor* a2)
{
	if(a1->isColliding(a2) || a1->hasBegunCollision(a2))
		a1->endCollision(a2);
	if(a2->isColliding(a1) || a2->hasBegunCollision(a1))
		a2->endCollision(a1);
	return;
}

void Collision::checkBoundingBox(Actor* a1, Actor* a2)
{
	sf::Vector2f pos1 = a1->getWorldPosition();
	sf::Vector2f pos2 = a2->getWorldPosition();
	if (pos1.x + a1->getCollisionBox().left + a1->getCollisionBox().width < pos2.x + a2->getCollisionBox().left)
	{
		endCollision(a1,a2);
		return;
	}
	if (pos1.x + a1->getCollisionBox().left > pos2.x + a2->getCollisionBox().left + a2->getCollisionBox().width)
	{
		endCollision(a1,a2);
		return;	
	}
	if (pos1.y + a1->getCollisionBox().top + a1->getCollisionBox().height < pos2.y + a2->getCollisionBox().top)
	{
		endCollision(a1,a2);
		return;	
	}
	if (pos1.y + a1->getCollisionBox().top > pos2.y + a2->getCollisionBox().top + a2->getCollisionBox().height)
	{
		endCollision(a1,a2);
		return;	
	}
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
	if(pos1.y + a1->getCollisionBox().top + a1->getCollisionBox().height < pos2.y + a2->getCollisionBox().top + a2->getCollisionBox().height)
	{
		a1Sides |= gf::Side::Bottom;
		a2Sides |= gf::Side::Top;
	}
	if(pos1.y + a1->getCollisionBox().top > pos2.y + a2->getCollisionBox().top)
	{
		a1Sides |= gf::Side::Top;
		a2Sides |= gf::Side::Bottom;
	}

	if(a1->hasBegunCollision(a2))
	{
		a1->duringCollision(a2,a1Sides);
	}
	else
	{
		a1->beginCollision(a2,a1Sides);
	}

	if(a2->hasBegunCollision(a1))
	{
		a2->duringCollision(a1,a1Sides);
	}
	else
	{
		a2->beginCollision(a1,a2Sides);
	}
	return;
}

