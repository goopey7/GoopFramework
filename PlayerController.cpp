//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#include "PlayerController.h"
#include <cmath>

PlayerController::PlayerController()
{
	
}

void PlayerController::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	for(auto binding : keyBindings)
	{
		if(sf::Keyboard::isKeyPressed(binding.first) && wasReleased[binding.first])
		{
			wasReleased[binding.first] = false;
			commands.push(pressedActions[binding.second]);
		}
		else if(!sf::Keyboard::isKeyPressed(binding.first) && !wasReleased[binding.first])
		{
			wasReleased[binding.first] = true;
			commands.push(releasedActions[binding.second]);
		}
	}
}

void PlayerController::handleHeldInput(CommandQueue& commands)
{
	for(auto binding : keyBindings)
	{
		if(sf::Keyboard::isKeyPressed(binding.first))
		{
			// ensures that only actions in the map
			// are pushed
			if(heldActions.count(binding.second) == 1)
			{
				commands.push(heldActions[binding.second]);
			}
		}
	}
}

void PlayerController::bindHeldKey(unsigned int action, sf::Keyboard::Key key, bool remap)
{
	// When remapping we don't want
	// the previous binding to still be mapped
	// to the action. At least for now
	if(remap)
	{
		for(auto binding : keyBindings)
		{
			if(binding.second == action)
			{
				keyBindings.erase(binding.first);
			}
		}
	}

	keyBindings[key] = action;
}

sf::Keyboard::Key PlayerController::getBindedKey(unsigned int action) const
{
	for(auto binding : keyBindings)
	{
		if(binding.second == action)
			return binding.first;
	}
	return sf::Keyboard::KeyCount;
}

