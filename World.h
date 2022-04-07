//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************


#pragma once

#include "SpriteNode.h"
#include "Actor.h"
#include "Collision.h"
#include "CommandQueue.h"
#include "ResourceHolder.h"

#include <fstream>
#include "Json.h"

class World : private sf::NonCopyable
{
	protected:
		// LayerCount will naturally return the number of layers before it
		// enums start at 0
		enum Layer
		{
			Background,
			Tile,
			Object,
			Entity,
			layerCount
		};

	public:
		explicit World(sf::RenderWindow& window);
		~World();
		
		void update(const float dt);
		void fixedUpdate(const float dt);
		void draw();
		CommandQueue& getCommandQueue();
		virtual void buildGraph();

		template <typename NodeChild>
		void addNode(std::unique_ptr<NodeChild>* node, Layer layer, bool bCollisionEnabled=false, bool bDynamicEnabled=false);

		void loadFromFile(const char* fileName, TextureHolder& textures);

	protected:
		sf::Vector2f spawnPos;
		sf::RenderWindow& window;

	private:
		// std::array behaves like a C array except it doesn't implicitly evaluate elements
		// as ptrs and adds additional functions such as size()
		std::array<Node*, layerCount> worldLayers;

		Node worldGraph;
		std::vector<Actor*> collidingActors;
		std::vector<Actor*> dynamicCollidingActors;
		CommandQueue commandQueue;

		//TODO DELETE
		sf::CircleShape c;
		sf::Vertex norm[2];
		//-----------
};

// collision should only be enabled if the node being passed in is an actor
template <typename NodeChild>
void World::addNode(std::unique_ptr<NodeChild>* node, Layer layer, bool bCollisionEnabled, bool bDynamicEnabled)
{
	if(bCollisionEnabled && !bDynamicEnabled)
		collidingActors.push_back(reinterpret_cast<Actor*>(node->get()));
	if(bCollisionEnabled && bDynamicEnabled)
		dynamicCollidingActors.push_back(reinterpret_cast<Actor*>(node->get()));
	worldLayers[layer]->attachChild(std::move(*node));
}

