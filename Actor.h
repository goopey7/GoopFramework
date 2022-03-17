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
		void setTexture(unsigned int texture);
		void setTextureRect(sf::IntRect textureRect);
		void scale(sf::Vector2f scaleFactor);
		void scale(float scaleX, float scaleY);
		void updateBox();

		bool isColliding(Actor* a);
		bool hasBegunCollision(Actor* a);

		void beginCollision(Actor* a, unsigned int sides);
		void duringCollision(Actor* a, unsigned int sides);
		void endCollision(Actor* a);

		virtual void onCollisionEnter(Actor* other, unsigned int sides);
		virtual void whileColliding(Actor* other, unsigned int sides);
		virtual void onCollisionExit(Actor* other);

	protected:
		sf::Sprite sprite;
		const TextureHolder& textures;

		sf::FloatRect collisionBox;
		bool bCollisionEnabled = false;

		sf::RectangleShape box;
		bool bDebugMode = false;
	private:
		std::map<Actor*,bool> collisionBegan;
		std::map<Actor*,bool> collisionDuring;
};

