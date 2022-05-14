//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include <SFML/Graphics.hpp>
#include "Category.h"
#include "Command.h"

// Nodes hold a ptr to their parent and smrt ptrs to all their children
// this allows us to recursively traverse every entity in the game
// Benefits: Coordinates relative to parent, broadcast to all nodes with ease
class Node : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		~Node();
		typedef std::unique_ptr<Node> NodePtr;
		void attachChild(NodePtr child);
		NodePtr detachChild(const Node& node);

		void fixedUpdate(const float dt);
		void update(const float dt);
		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;
		virtual unsigned int getCategory() const;
		void onCommand(const Command& command, const float dt);
		// final means that children of this class cannot override it
		// draw renders the entire node and children
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

		void die();
		void spawn(NodePtr* node);
		std::vector<NodePtr*>& getPendingSpawn();
		bool shouldDie() const;

		void killChildren();

	private:
		std::vector<NodePtr> children;
		Node* parent = nullptr;

		// only draws the current node but not it's children
		virtual void drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const;

		// children are expected to override their respective 'current' methods
		virtual void fixedUpdateCurrent(const float dt){};
		void fixedUpdateChildren(const float dt);
		virtual void updateCurrent(const float dt){};
		void updateChildren(const float dt);

		bool bShouldDie = false;

		std::vector<NodePtr*> toSpawn;
};
