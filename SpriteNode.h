//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#pragma once

#include "Node.h"

// This class is when we want to just draw an image to the screen
// Good for backgrounds and stuff
class SpriteNode : public Node
{
	public:
		// explicit means that this constructor cannot be used implicitly
		// ie. cannot take a texture and infer to use this constructor and make a SpriteNode
		// for clearer example read this: 
		//https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
		explicit SpriteNode(const sf::Texture& texture);
		SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

	private:
		sf::Sprite sprite;
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

