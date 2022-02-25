//Copyright Sam Collier 2022

#include "Tux.h"

Tux::Tux(const TextureHolder& textures)
	: Actor(textures)
{
	sprite.setTexture(textures.get(Textures::Tux));
	setPosition(100.f,100.f);
}

void Tux::updateCurrent(const float dt)
{
	move(velocity*dt);
}

void Tux::fixedUpateCurrent(const float dt)
{
}

sf::Vector2f Tux::getVelocity() const
{
	return velocity;
}

void Tux::setVelocity(sf::Vector2f v)
{
	velocity = v;
}

void Tux::setVelocityX(float vx)
{
	velocity.x = vx;
}

void Tux::setVelocityY(float vy)
{
	velocity.y = vy;
}

unsigned int Tux::getCategory() const
{
	return Category::PlayerCharacter;
}

