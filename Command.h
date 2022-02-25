//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 4 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#pragma once

#include <functional>
#include "Category.h"

class Node;
struct Command
{
	Command();
	std::function<void(Node&,const float dt)> action; // The command
	unsigned int category; // The category the command is for
};

// this void function takes the Node reference and down casts it to the desired child
// which allows us to have a reference to the child class and its functionality
// while maintaining the above interface
template <typename NodeChild, typename Function>
std::function<void(Node&, const float)> derivedAction(Function fn)
{
	// This lambda expression uses a capture list '[=]'
	// means that the parameters are passed by value
	return [=] (Node& node, const float dt)
	{
		fn(static_cast<NodeChild&>(node),dt);
	};
}
// derivedAction acts as an adapter for when we build commands
// it makes the implementation of command actions look cleaner
// since it deals with the casting for us

