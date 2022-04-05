//Copyright Sam Collier 2022

#include "Actor.h"

Actor::Actor(const TextureHolder& textures)
	: textures(textures)
{
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red);
	box.setPosition(getPosition());
	box.setOutlineThickness(1.f);
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

void Actor::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const { target.draw(sprite,states);
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
}

void Actor::setTexture(unsigned int texture)
{
	sprite.setTexture(textures.get(texture));
}

void Actor::scale(sf::Vector2f scaleFactor)
{
	sprite.setScale(scaleFactor);
	updateBox();
}

void Actor::scale(float scaleX, float scaleY)
{
	sprite.setScale(scaleX,scaleY);
	updateBox();
}

void Actor::updateBox()
{
	collisionBox.width *= sprite.getScale().x;
	collisionBox.height *= sprite.getScale().y;
	box.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
}


void Actor::onCollision()
{

}

void Actor::onCollisionExit()
{
}

sf::Vector2u Actor::getTextureSize()
{
	return sprite.getTexture()->getSize();
}

