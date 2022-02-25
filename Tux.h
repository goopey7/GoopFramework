//Copyright Sam Collier 2022
#pragma once

#include "Actor.h"

class Tux : public Actor
{
	public:
		Tux(const TextureHolder& textures);

		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpateCurrent(const float dt) override;

	protected:

	private:
		sf::Vector2f velocity = {100.f,0.f};
		
};

