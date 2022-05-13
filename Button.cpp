//Copyright Sam Collier 2022

#include "Button.h"

Button::Button(sf::RenderWindow& window, sf::Vector2f topLeft, sf::Vector2f size, sf::Font& font, std::string textStr)
	: window(&window), font(font)
{
	box.setPosition(topLeft);
	box.setSize(size);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Green);
	box.setOutlineThickness(1.f);
	text.setFont(font);
	text.setString(textStr);
	text.setCharacterSize(15.f);
	text.setOrigin(text.getGlobalBounds().width/2.f,text.getGlobalBounds().height/2.f);
	text.setPosition(box.getPosition() + Vector<float>::divide(box.getSize(),2.f));
}

Button::~Button()
{
}

bool Button::isHovered()
{
	sf::Vector2i mousePixelCoord = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePos = window->mapPixelToCoords(mousePixelCoord);
	return Collision::RectVPoint(&box,mousePos);
}

bool Button::isClicked()
{
	if(bWasClicked)
		return false;
	bWasClicked = isHovered() && sf::Mouse::isButtonPressed(sf::Mouse::Left);
	return bWasClicked;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(box,states);
	target.draw(text,states);
}

bool Button::isHeld()
{
	return bWasClicked && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Button::isReleased()
{
	if(!bWasClicked)
		return false;
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bWasClicked = false;
		return true;
	}
	else return false;
}

bool Button::isHovered(sf::Color fillColor)
{
	if(isHovered())
	{
		box.setFillColor(fillColor);
		return true;
	}
	return false;
}

bool Button::isClicked(sf::Color fillColor)
{
	if(isClicked())
	{
		box.setFillColor(fillColor);
		return true;
	}
	return false;
}

bool Button::isHeld(sf::Color fillColor)
{
	if(isHeld())
	{
		box.setFillColor(fillColor);
		return true;
	}
	return false;
}

bool Button::isReleased(sf::Color fillColor)
{
	if(isReleased())
	{
		box.setFillColor(fillColor);
		return true;
	}
	return false;
}

void Button::setFillColor(sf::Color fillColor)
{
	box.setFillColor(fillColor);
}

