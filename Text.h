//Copyright Sam Collier 2022
#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"

enum Anchor
{
	BottomLeft,
	BottomRight,
	TopLeft,
	TopRight,
	Center,
};
class Text : public sf::Drawable
{
	public:
		Text(sf::RenderWindow& window, sf::Vector2f pos, sf::Font& font,std::string text);
		Text(sf::RenderWindow& window,sf::Font& font);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
		void setText(std::string text);
		void anchorTo(Anchor anchor);
		void updatePosFromAnchor();
		void setPosition(sf::Vector2f pos);

	protected:

	private:
		sf::RenderWindow* window;
		sf::Font font;
		sf::Text text;
		Anchor anchor;
};

