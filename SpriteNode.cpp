//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(sprite,states);
}
