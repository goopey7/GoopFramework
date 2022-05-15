//Copyright Sam Collier 2022
#pragma once

#include "Collision.h"
#include "Vector.h"

class Button : public sf::Drawable
{
	public:
		Button(sf::RenderWindow& window, sf::Vector2f topLeft, sf::Vector2f size, sf::Font& font, std::string text);
		~Button();
		bool isHovered();
		bool isHovered(sf::Color fillColor);
		bool isClicked();
		bool isClicked(sf::Color fillColor);
		bool isHeld();
		bool isHeld(sf::Color fillColor);
		bool isReleased();
		bool isReleased(sf::Color fillColor);
		void setFillColor(sf::Color fillColor);
		void setPosition(sf::Vector2f pos);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	private:
		sf::RenderWindow* window;
		sf::Font font;
		sf::Text text;
		sf::RectangleShape box;
		bool bWasClicked = false;
};

