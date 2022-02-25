//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#include "World.h"

World::World(sf::RenderWindow& window)
	: window(window),spawnPos(100.f,100.f)
{
	loadTextures();
	buildGraph();
}


void World::loadTextures()
{
	textures.load(Textures::Tux,"art/tux.png");
	textures.load(Textures::Terminal,"art/bkg.jpg");
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

	// Tux Entity
	std::unique_ptr<Tux> tux(new Tux(textures));
	tux->setPosition(spawnPos);
	worldLayers[Foreground]->attachChild(std::move(tux));

	// bkg
	std::unique_ptr<SpriteNode> bkg(new SpriteNode(textures.get(Textures::Terminal)));
	bkg->setPosition(0.f,0.f);
	bkg->scale(4.f,4.f);
	worldLayers[Background]->attachChild(std::move(bkg));
}

void World::update(const float dt)
{
	worldGraph.update(dt);
}

void World::fixedUpdate(const float dt)
{
	worldGraph.fixedUpdate(dt);
}

void World::draw()
{
	window.draw(worldGraph);
}

World::~World()
{
}

