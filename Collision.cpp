//Copyright Sam Collier 2022

#include "Collision.h"
#include <cmath>

bool Collision::ActorVPoint(const Actor* a, const sf::Vector2f point)
{
	sf::FloatRect box = a->getCollisionBox();
	sf::Vector2f aLocation = a->getWorldPosition();
	
	// does the point lie within the bounds of the box?
	return (point.x >= aLocation.x + box.left && point.x <= aLocation.x + box.width
			&& point.y >= aLocation.y + box.top && point.y <= aLocation.y + box.height);
}

bool Collision::ActorVActor(const Actor* a1, const Actor* a2)
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



bool Collision::RayVsActor(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDir, const Actor* a,
		sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime)
{
	sf::Vector2f nearPoint = Vector<float>::divide(a->getWorldPosition() + a->getCollisionBoxPos() - rayOrigin, rayDir);
	sf::Vector2f farPoint = Vector<float>::divide(a->getWorldPosition() + a->getCollisionBoxPos() + a->getCollisionBoxSize() - rayOrigin, rayDir);

	if (std::isnan(farPoint.y) || std::isnan(farPoint.y)) return false;
	if (std::isnan(nearPoint.y) || std::isnan(nearPoint.x)) return false;

	// swap components around so they actually are near and far
	if(nearPoint.x > farPoint.x) std::swap(nearPoint.x,farPoint.x);
	if(nearPoint.y > farPoint.y) std::swap(nearPoint.y,farPoint.y);

	if(nearPoint.x > farPoint.y || nearPoint.y > farPoint.x)
		return false;

	float nearT = std::max(nearPoint.x,nearPoint.y);
	float farT = std::min(farPoint.x,farPoint.y);

	if(farT < 0 || nearT > 1.f) return false;

	contactPoint = rayOrigin + rayDir*nearT;

	if(nearPoint.x > nearPoint.y)
	{
		if(rayDir.x < 0)
			contactNormal = {1,0};
		else
			contactNormal = {-1,0};
	}
	else if(nearPoint.x < nearPoint.y)
	{
		if(rayDir.y < 0)
			contactNormal = {0,1};
		else
			contactNormal = {0,-1};
	}
	hitTime = nearT;
	return true;
}

bool Collision::MovingActorVActor(const Actor* mA, const Actor* sA, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	if(mA->getVelocity().x == 0.f && mA->getVelocity().y == 0.f)
		return false;

	sf::Vector2f sATopLeft = sf::Vector2f(sA->getCollisionBox().left , sA->getCollisionBox().top);
	sf::Vector2f mATopLeft = sf::Vector2f(mA->getCollisionBox().left , mA->getCollisionBox().top);

	sf::FloatRect expandedRect = 
		sf::FloatRect(sA->getWorldPosition() + sATopLeft - mA->getCollisionBoxSize() / 2.f,
		mA->getCollisionBoxSize() + sA->getCollisionBoxSize());

	// TODO CLEAN THIS AWFULNESS UP
	TextureHolder t;
	Actor expandedBox(t,nullptr);
	expandedBox.setCollisionBox(expandedRect);
	expandedBox.setPosition(0.f,0.f);
	// -------------------------------

	if(RayVsActor(mA->getWorldPosition() + mATopLeft + mA->getCollisionBoxSize() / 2.f, mA->getVelocity() * dt,&expandedBox,contactPoint,contactNormal,hitTime))
	{
		if(std::abs(hitTime) >= 0.f && std::abs(hitTime) <= 1.f)
			return true;
	}

	return false;
}

void Collision::ResolveDynamicVStatic(Actor* dA, Actor* sA, const float dt)
{
	sf::Vector2f cp,cn;
	float ct = 0.f;
	if(Collision::MovingActorVActor(dA,sA,cp,cn,ct,dt))
	{
		sf::Vector2f vel = dA->getVelocity();
		sf::Vector2f newVel = Vector<float>::multiply(cn,sf::Vector2f(std::abs(vel.x),std::abs(vel.y))) * (1-ct);
		dA->setVelocity(vel + newVel);
		dA->onCollisionEnter(sA,cp,cn,ct,dt);
	}
}

