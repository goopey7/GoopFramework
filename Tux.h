//Copyright Sam Collier 2022
#pragma once

#include "Actor.h"

class Tux : public Actor
{
	public:
		Tux(const TextureHolder& textures);

		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpateCurrent(const float dt) override;
		virtual unsigned int getCategory() const override;
		sf::Vector2f getVelocity() const;
		void setVelocity(sf::Vector2f v);
		void setVelocityX(float vx);
		void setVelocityY(float vy);

	protected:

	private:
		sf::Vector2f velocity = {0.f,0.f};
		
};

