//Copyright Sam Collier 2022
#pragma once

#include "ResourceHolder.h"
#include "Node.h"

typedef ResourceHolder<sf::Texture,unsigned int> TextureHolder;

class Actor : public Node
{
	public:
		Actor(const TextureHolder& textures);
		~Actor();

		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual unsigned int getCategory() const override;

	protected:
		sf::Sprite sprite;
		const TextureHolder& textures;
};

