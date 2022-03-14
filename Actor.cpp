//Copyright Sam Collier 2022

#include "Actor.h"

Actor::Actor(const TextureHolder& textures)
	: textures(textures)
{
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(1.f);
	box.setPosition(getWorldPosition());
}

Actor::~Actor()
{
}

void Actor::updateCurrent(const float dt)
{
	box.setPosition(getWorldPosition());
}

void Actor::fixedUpateCurrent(const float dt)
{
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite,states);
	if(bDebugMode)
		target.draw(box,states);
}

unsigned int Actor::getCategory() const
{
	return Category::None;
}

sf::FloatRect Actor::getCollisionBox() const
{
	return collisionBox;
}

void Actor::onCollision(Actor* other)
{
}

void Actor::setCollisionBox(sf::FloatRect box)
{
	this->collisionBox = box;
	this->box.setSize(sf::Vector2f(box.width,box.height));
}

void Actor::toggleDebugMode()
{
	bDebugMode = !bDebugMode;
}

