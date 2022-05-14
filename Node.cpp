//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#include "Node.h"
#include <iostream>

void Node::attachChild(NodePtr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

Node::NodePtr Node::detachChild(const Node& node)
{
	int childFound = -1;
	for(int i=0;i<children.size();i++)
	{
		if(children[i].get() == &node)
		{
			childFound = i;
			break;
		}
	}

	assert(childFound >= 0);

	NodePtr returnNode = std::move(children[childFound]);
	returnNode->parent = nullptr;
	children.erase(children.begin() + childFound);
	return returnNode;
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Two transforms are applied one after the other using the * operator

	// This takes the parent's absolute transform and then applies the current node's
	// relative transform. So this achieves the absolute world transform of the current node
	// this is also how sf::Sprite handles it by combining it's own transform with the passed
	// render state
	states.transform *= getTransform();

	// now that we have the absolute transform we can draw the node
	drawCurrent(target,states);

	// recursively draw all children
	for(const NodePtr& child : children)
	{
		child->draw(target,states);
	}

}

void Node::fixedUpdateChildren(const float dt)
{
	for(NodePtr &child : children)
		child->fixedUpdate(dt);
}

void Node::updateChildren(const float dt)
{
	for(NodePtr &child : children)
		child->update(dt);
}

void Node::fixedUpdate(const float dt)
{
	fixedUpdateCurrent(dt);
	fixedUpdateChildren(dt);
} 

void Node::update(const float dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Transform Node::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	// Get absolute transform by accumulating all the transformations up the tree
	// until we reach the root node. That will yield world transform ie. transform relative
	// to root node. same thing
	for(const Node* node = this; node != nullptr; node = node->parent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

sf::Vector2f Node::getWorldPosition() const
{
	// Apply transformation of world pos with origin
	// to get position relative to origin ie world coords
	return getWorldTransform() * sf::Vector2f();
}

unsigned int Node::getCategory() const
{
	return Category::None;
}

void Node::onCommand(const Command& command, const float dt)
{
	// Check if categories match using bitwise AND '&'
	// if two bits in the same place match then we have a match in category
	// and the action is intended for this node
	// so it is executed
	if(command.category & getCategory())
		command.action(*this,dt);

	// Broadcast command to all children
	for(NodePtr& child : children)
		child->onCommand(command,dt);
}

void Node::die()
{
	bShouldDie = true;
}

bool Node::shouldDie() const
{
	return bShouldDie;
}

void Node::killChildren()
{
	for(int i=0;i<children.size();i++)
	{
		children[i]->killChildren();
		if(children[i]->shouldDie())
		{
			detachChild(*children[i].get());
			//children[i].release();
		}
	}
}

Node::~Node()
{
}

void Node::spawn(NodePtr* node)
{
	if(parent == nullptr)
		toSpawn.push_back(node);
	else
		parent->spawn(node);
}

std::vector<Node::NodePtr*>& Node::getPendingSpawn()
{
	return toSpawn;
}

void Node::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

