//Copyright Sam Collier 2022
#pragma once

#include "Collision.h"
#include "Vector.h"

class Button : public sf::Drawable
{
	public:
		Button(sf::RenderWindow& window, sf::Vector2f topLeft, sf::Vector2f bottomRight, std::string text);
		~Button();
		bool isClicked();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	private:
		sf::RenderWindow* window;
		sf::Font font;
		sf::Text text;
		sf::RectangleShape box;
};

