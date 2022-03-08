//Copyright Sam Collier 2022
#pragma once

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#include "../Tux.h"
#include "CommandQueue.h"

class PlayerController
{
	public:
		PlayerController();
		
		void bindHeldKey(unsigned int heldAction, sf::Keyboard::Key key, bool remap = true);
		sf::Keyboard::Key getBindedKey(unsigned int action) const;

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleHeldInput(CommandQueue& commands);
	protected:
		std::map<sf::Keyboard::Key, bool> wasReleased;
		std::map<sf::Keyboard::Key, unsigned int> keyBindings;
		std::map<unsigned int,Command> pressedActions;
		std::map<unsigned int,Command> heldActions;
		std::map<unsigned int,Command> releasedActions;

		const float playerSpeed = 500.f;

};

