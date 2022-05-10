//Copyright Sam Collier 2022

#include "Line.h"

Line::Line(sf::Vector2f p1, sf::Vector2f p2, float thickness)
{
	setPoints(p1,p2);
}

void Line::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(line,2,sf::Lines,states);
}

void Line::setPoints(sf::Vector2f p1, sf::Vector2f p2)
{
	line[0] = sf::Vertex(p1);
	line[1] = sf::Vertex(p2);
}

Line::Line()
{
	setPoints({0.f,0.f},{0.f,0.f});
}

