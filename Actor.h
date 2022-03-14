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
		virtual void onCollision(Actor* other);
		sf::FloatRect getCollisionBox() const;
		void setCollisionBox(sf::FloatRect box);
		void toggleDebugMode();
		void setTexture(unsigned int texture);
		void setTextureRect(sf::IntRect textureRect);

	protected:
		sf::Sprite sprite;
		const TextureHolder& textures;

		sf::FloatRect collisionBox;
		bool bCollisionEnabled = false;

		sf::RectangleShape box;
		bool bDebugMode = false;
};

