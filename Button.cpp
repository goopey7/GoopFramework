//Copyright Sam Collier 2022

#include "Button.h"

Button::Button(sf::RenderWindow& window, sf::Vector2f topLeft, sf::Vector2f bottomRight, sf::Font& font, std::string textStr)
	: window(&window), font(font)
{
	box.setPosition(topLeft);
	box.setSize(bottomRight-topLeft);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Green);
	box.setOutlineThickness(10.f);
	text.setFont(font);
	text.setString(textStr);
	text.setCharacterSize(24);
	text.setOrigin(text.getGlobalBounds().width/2.f,text.getGlobalBounds().height/2.f);
	text.setPosition(box.getPosition()+Vector<float>::divide(box.getSize(),2.f));
}

Button::~Button()
{
}

bool Button::isClicked()
{
	sf::Vector2i mousePixelCoord = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePos = window->mapPixelToCoords(mousePixelCoord);
	return sf::Mouse::isButtonPressed(sf::Mouse::Left)
		&& Collision::RectVPoint(&box,mousePos);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box,states);
	target.draw(text,states);
}
