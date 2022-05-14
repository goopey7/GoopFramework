//Copyright Sam Collier 2022
#pragma once

#include "ResourceHolder.h"
#include "Node.h"
#include "CollisionHelpers.h"

typedef ResourceHolder<sf::Texture,unsigned int> TextureHolder;

class World;

class Actor : public Node
{
	public:
		Actor(const TextureHolder& textures, World* currentWorld);
		~Actor();

		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpdateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
		virtual unsigned int getCategory() const override;
		void setCategory(unsigned int category);
		sf::Vector2f getVelocity() const;
		void setVelocity(sf::Vector2f vel);
		sf::FloatRect getCollisionBox() const;
		sf::Vector2f getCollisionBoxSize() const;
		sf::Vector2f getCollisionBoxPos() const;
		void setCollisionBox(sf::FloatRect box);
		void toggleDebugMode();
		sf::Vector2u getTextureSize();
		void setTexture(unsigned int texture);
		void setTextureRect(sf::IntRect textureRect);
		void scale(sf::Vector2f scaleFactor);
		void scale(float scaleX, float scaleY);
		void updateBox();
		bool isDynamic() const;
		void setIsDynamic(bool isDynamic);
		bool collisionEnabled();
		void enableCollision(bool shouldCollide);
		const TextureHolder& getTextures() const;

		World* getWorld();

		virtual void onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt);
		virtual void onDynamicVsDynamicEnter(Actor* other);

		void applyDamage(float damage);
		float getDamage();

	protected:
		sf::Sprite sprite;
		const TextureHolder& textures;

		sf::FloatRect collisionBox;

		sf::RectangleShape box;
		bool bDebugMode = false;

		sf::Vector2f velocity;
		float rotationSpeed = 0.f;

		bool bCollisionEnabled=false;
		bool bIsDynamic=false;

		World* currentWorld;

		float health = 100.f;
		float damage = 10.f;

		unsigned int category = Category::Actor;
};

