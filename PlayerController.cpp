//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#include "PlayerController.h"
#include <cmath>

enum StopDir
{
	None,
	Up,
	Left,
	Down,
	Right,
};

struct TuxMover
{
	TuxMover(float vx, float vy, StopDir dir = StopDir::None)
		: velocity(vx,vy),dir(dir)
	{
	}

	TuxMover(StopDir dir)
		: dir(dir)
	{
	}

	void operator() (Tux& tux, const float dt) const
	{
		switch(dir)
		{
			case StopDir::Up:
			{
				if(tux.getVelocity().y < 0)
					tux.setVelocityY(0.f);
				break;
			}
			case StopDir::Left:
			{
				if(tux.getVelocity().x < 0)
					tux.setVelocityX(0.f);
				break;
			}
			case StopDir::Down:
			{
				if(tux.getVelocity().y > 0)
					tux.setVelocityY(0.f);
				break;
			}
			case StopDir::Right:
			{
				if(tux.getVelocity().x > 0)
					tux.setVelocityX(0.f);
				break;
			}
			case StopDir::None:
			{
				if(velocity.x != 0)
					tux.setVelocityX(velocity.x);
				if(velocity.y != 0)
					tux.setVelocityY(velocity.y);

				// keep velocity constant using 45 - 45 - 90 rule
				if((tux.getVelocity().y != 0.f && tux.getVelocity().x != 0.f))
				{
					if(velocity.x != 0.f)
						tux.setVelocityX(velocity.x/sqrtf(2.f));
					else if(velocity.y != 0.f)
						tux.setVelocityY(velocity.y/sqrtf(2.f));
				}

				if(fabs(tux.getVelocity().x) >= fabs(tux.getVelocity().y * sqrtf(2.f))
						&& tux.getVelocity().y != 0.f)
						tux.setVelocityX(tux.getVelocity().x/sqrtf(2.f));

				if(fabs(tux.getVelocity().y) >= fabs(tux.getVelocity().x * sqrtf(2.f))
						&& tux.getVelocity().x != 0.f)
						tux.setVelocityY(tux.getVelocity().y/sqrtf(2.f));
			}

		}

		if(dir==StopDir::Right || dir == StopDir::Left)
			tux.setVelocityY(tux.getVelocity().y*sqrt(2.f));

		if(dir==StopDir::Up || dir == StopDir::Down)
			tux.setVelocityX(tux.getVelocity().x*sqrt(2.f));
		std::cout << tux.getVelocity().x << ',' << tux.getVelocity().y << '\n';
	}

	sf::Vector2f velocity;
	StopDir dir;
};

PlayerController::PlayerController()
{
	keyBindings[sf::Keyboard::W] = MoveUp;
	keyBindings[sf::Keyboard::A] = MoveLeft;
	keyBindings[sf::Keyboard::S] = MoveDown;
	keyBindings[sf::Keyboard::D] = MoveRight;
	keyBindings[sf::Keyboard::P] = ShowPos;

	// Pressed Actions
	pressedActions[MoveUp].action = derivedAction<Tux>(TuxMover(0.f,-playerSpeed));
	pressedActions[MoveLeft].action = derivedAction<Tux>(TuxMover(-playerSpeed,0.f));
	pressedActions[MoveDown].action = derivedAction<Tux>(TuxMover(0.f,playerSpeed));
	pressedActions[MoveRight].action = derivedAction<Tux>(TuxMover(playerSpeed,0.f));
	pressedActions[ShowPos].action = [] (Node& node, const float dt)
	{
		std::cout << node.getPosition().x << ',' << node.getPosition().y << '\n';
	};

	// Held Actions

	// Released Actions
	releasedActions[MoveUp].action = derivedAction<Tux>(TuxMover(StopDir::Up));
	releasedActions[MoveLeft].action = derivedAction<Tux>(TuxMover(StopDir::Left));
	releasedActions[MoveDown].action = derivedAction<Tux>(TuxMover(StopDir::Down));
	releasedActions[MoveRight].action = derivedAction<Tux>(TuxMover(StopDir::Right));

	// Init categroies
	for(auto &binding : heldActions)
	{
		binding.second.category = Category::PlayerCharacter;
	}
	for(auto &binding : pressedActions)
	{
		binding.second.category = Category::PlayerCharacter;
	}
	for(auto &binding : releasedActions)
	{
		binding.second.category = Category::PlayerCharacter;
	}
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

void PlayerController::bindHeldKey(Action action, sf::Keyboard::Key key, bool remap)
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

sf::Keyboard::Key PlayerController::getBindedKey(Action action) const
{
	for(auto binding : keyBindings)
	{
		if(binding.second == action)
			return binding.first;
	}
	return sf::Keyboard::KeyCount;
}

