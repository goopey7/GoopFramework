//Copyright Sam Collier 2022

#include "Actor.h"

Actor::Actor(const TextureHolder& textures)
	: textures(textures)
{
}

Actor::~Actor()
{
}

void Actor::updateCurrent(const float dt)
{
}

void Actor::fixedUpateCurrent(const float dt)
{
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite,states);
}

