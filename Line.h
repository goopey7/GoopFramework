//Copyright Sam Collier 2022
#pragma once

#include "Node.h"

class Line : public Node
{
	public:
		Line(sf::Vector2f p1, sf::Vector2f p2, float thickness);
		Line();
		void setPoints(sf::Vector2f p1, sf::Vector2f p2);

	private:
		sf::Vertex line[2];
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};

