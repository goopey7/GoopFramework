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

