//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#include "World.h"

World::World(sf::RenderWindow& window)
	: window(window),spawnPos(100.f,100.f)
{
	buildGraph();
}

void World::buildGraph()
{
	// Initialize Layers
	for(int i=0;i<layerCount;i++)
	{
		Node::NodePtr layer(new Node());
		worldLayers[i] = layer.get();
		worldGraph.attachChild(std::move(layer));
	}
}

void World::update(const float dt)
{
	worldGraph.update(dt);
}

void World::fixedUpdate(const float dt)
{
	// Broadcast commands to sceneGraph
	while(!commandQueue.isEmpty())
		worldGraph.onCommand(commandQueue.pop(),dt);

	worldGraph.fixedUpdate(dt);

	// check collisions
	for(int i=0;i<collidingActors.size()-1;i++)
	{
		for(int j=i+1; j<collidingActors.size();j++)
		{
			if(Collision::checkBoundingBox(collidingActors[i], collidingActors[j]))
			{
				collidingActors[i]->onCollision(collidingActors[j]);
				collidingActors[j]->onCollision(collidingActors[i]);
			}
		}
	}
}

void World::draw()
{
	window.draw(worldGraph);
}

World::~World()
{
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue;
}

