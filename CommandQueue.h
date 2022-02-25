//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#pragma once

#include <queue>
#include "Command.h"

// Basic wrapper for std::queue for distributing commands
class CommandQueue
{
	public:
		void push(const Command& command);
		Command pop();
		bool isEmpty();

	private:
		std::queue<Command> queue;
};

