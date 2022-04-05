//Copyright Sam Collier 2022
#pragma once

#include "ResourceHolder.h"
#include "Node.h"
#include "CollisionHelpers.h"

typedef ResourceHolder<sf::Texture,unsigned int> TextureHolder;

class Actor : public Node
{
	public:
		Actor(const TextureHolder& textures);
		~Actor();

		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
		virtual unsigned int getCategory() const override;
		sf::FloatRect getCollisionBox() const;
		void setCollisionBox(sf::FloatRect box);
		void toggleDebugMode();
		sf::Vector2u getTextureSize();
		void setTexture(unsigned int texture);
		void setTextureRect(sf::IntRect textureRect);
		void scale(sf::Vector2f scaleFactor);
		void scale(float scaleX, float scaleY);
		void updateBox();

		bool isColliding(Actor* a);
		bool hasBegunCollision(Actor* a);

		virtual void onCollision();
		virtual void onCollisionExit();

		
	protected:
		sf::Sprite sprite;
		const TextureHolder& textures;

		sf::FloatRect collisionBox;
		bool bCollisionEnabled = false;

		sf::RectangleShape box;
		bool bDebugMode = false;

	private:
};

