//Copyright Sam Collier 2022

#include "Actor.h"

Actor::Actor(const TextureHolder& textures)
	: textures(textures)
{
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(1.f);
	box.setPosition(getPosition());
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
	if(bDebugMode)
		target.draw(box,states);
}

unsigned int Actor::getCategory() const
{
	return Category::Actor;
}

sf::FloatRect Actor::getCollisionBox() const
{
	return collisionBox;
}

void Actor::onCollision(Actor* other)
{
}

void Actor::setCollisionBox(sf::FloatRect box)
{
	this->collisionBox = box;
	this->box.setPosition(box.left,box.top);
	this->box.setSize(sf::Vector2f(box.width,box.height));
}

void Actor::toggleDebugMode()
{
	bDebugMode = !bDebugMode;
}

void Actor::setTextureRect(sf::IntRect textureRect)
{
	sprite.setTextureRect(textureRect);
	collisionBox.width = sprite.getTextureRect().width;
	collisionBox.height = sprite.getTextureRect().height;
	box.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
}

void Actor::setTexture(unsigned int texture)
{
	sprite.setTexture(textures.get(texture));
	collisionBox.width = sprite.getTextureRect().width * sprite.getScale().x;
	collisionBox.height = sprite.getTextureRect().height * sprite.getScale().y;
	box.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
}

