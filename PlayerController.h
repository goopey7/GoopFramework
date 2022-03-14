//Copyright Sam Collier 2022
#pragma once

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#include "CommandQueue.h"
#include <SFML/Window.hpp>
#include <map>

class PlayerController
{
	public:
		PlayerController();
		
		void bindKey(unsigned int action, sf::Keyboard::Key key, bool remap = true);
		void bindMouseButton(unsigned int action, sf::Mouse::Button, bool remap = true);

		sf::Keyboard::Key getBindedKey(unsigned int action) const;
		sf::Mouse::Button getBindedMouseButton(unsigned int action) const;

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleHeldInput(CommandQueue& commands);

	protected:
		std::map<sf::Keyboard::Key, bool> wasKeyReleased;
		std::map<sf::Mouse::Button, bool> wasMouseButtonReleased;
		std::map<sf::Keyboard::Key, unsigned int> keyBindings;
		std::map<sf::Mouse::Button, unsigned int> mouseBindings;
		std::map<unsigned int,Command> pressedActions;
		std::map<unsigned int,Command> heldActions;
		std::map<unsigned int,Command> releasedActions;
};

