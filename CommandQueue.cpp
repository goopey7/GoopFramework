//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	queue.push(command);
}

Command CommandQueue::pop()
{
	Command popped = queue.front();
	queue.pop();
	return popped;
}

bool CommandQueue::isEmpty()
{
	return queue.empty();
}

