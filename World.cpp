//Copyright Sam Collier 2022

//**************************************************************************************
//Heavily influenced by 
//Chapter 3 of SFML Game Development by Artur Moreira, Henrik V. Hansson, and Jan Haller
//**************************************************************************************

#include "World.h"
#include "Vector.h"

World::World(sf::RenderWindow& window, std::unique_ptr<World>* currentWorld)
	: window(window),currentWorld(currentWorld),spawnPos(100.f,100.f)
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

	// check dynamic vs static collisions
	for(int i=0;i<dynamicCollidingActors.size();i++)
	{
		for(int j=0;j<collidingActors.size();j++)
		{
			Collision::ResolveDynamicVStatic(dynamicCollidingActors[i], collidingActors[j], dt);
		}
	}

	// check dynamic vs dynamic collisions
	for(int i=0;i<dynamicCollidingActors.size();i++)
	{
		Actor* a1 = dynamicCollidingActors[i];
		if(!a1->isDynamic())
		{
			dynamicCollidingActors.erase(dynamicCollidingActors.begin() + i);
		}
		else
		{
			for(int j=i+1;j<dynamicCollidingActors.size();j++)
			{
				Actor* a2 = dynamicCollidingActors[j];
				if(!a2->isDynamic())
				{
					dynamicCollidingActors.erase(dynamicCollidingActors.begin() + j);
				}
				else
				{
					if(Collision::ActorVActor(a1,a2))
					{
						a1->onDynamicVsDynamicEnter(a2);
						a2->onDynamicVsDynamicEnter(a1);
					}
				}
			}
		}
	}

	worldGraph.fixedUpdate(dt);

	// any child wanting to die will die at this time
	// this sounds very weird out of context lol
	for(int i=0;i<dynamicCollidingActors.size();i++)
	{
		if(dynamicCollidingActors[i]->shouldDie())
		{
			dynamicCollidingActors.erase(dynamicCollidingActors.begin() + i);
		}
	}
	for(int j=0;j<collidingActors.size();j++)
	{
		if(collidingActors[j]->shouldDie())
		{
			collidingActors.erase(collidingActors.begin() + j);
		}
	}
	worldGraph.killChildren();

	// SPAWN AWAITING ITEMS
	std::vector<Node::NodePtr*>* pendingSpawn = &worldGraph.getPendingSpawn();
	for(int i=0;i<pendingSpawn->size();i++)
	{
		addNode(&*(*pendingSpawn)[i],Layer::Entity);
	}
	pendingSpawn->clear();
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

void World::loadFromFile(const char* fileName, Player& sfx,TextureHolder& textures, unsigned int numTextures)
{
	using nlohmann::json;
	std::ifstream file(fileName);
	json map = json::parse(file);
	json layers = map["layers"];
	std::map<std::string,int> tileSets;
	for(int i=0; i<map["tilesets"].size();i++)
	{
		tileSets[map["tilesets"].at(i)["image"]] = map["tilesets"].at(i)["firstgid"];
	}
	std::cout << "\n===============================\n";
	for(auto pair : tileSets)
	{
		std::cout << pair.first << " /// " << pair.second << '\n';
	}
	int mapWidth = map["width"], mapHeight = map["height"];
	int tileWidth = map["tilewidth"], tileHeight = map["tileheight"];

	unsigned int textureID = numTextures;

	for(auto pair : tileSets)
	{
		textures.load(textureID++,pair.first);
	}

	for(json layer : layers)
	{
		if(!layer["data"].is_null())
		{
			std::vector<int> layout = layer["data"];
			int i = 0;
			for(int y = 0; y<mapHeight; y++)
			{
				for(int x = 0; x<mapWidth; x++)
				{
					if(layout[i] != 0)
					{
						std::unique_ptr<Actor> tile(new Actor(sfx,textures,this));
						tile->setTexture(textureID-1);
						tile->setPosition(x*tileWidth,y*tileHeight);
						sf::IntRect texRect = sf::IntRect(
									(layout[i]-1)*tileWidth,0,
									tileWidth,tileHeight);
						tile->setTextureRect(texRect);
						addNode(&tile,Tile);
					}
					i++;
				}
			}
		}
		if(!layer["objects"].is_null())
		{
			for(json object : layer["objects"])
			{
				sf::FloatRect rect = sf::FloatRect(object["x"],object["y"],object["width"],object["height"]);
				if(object["properties"].at(0)["name"] == "colType")
				{
					if(object["properties"].at(0)["value"] == "block")
					{
						std::unique_ptr<Actor> colBox(new Actor(sfx,textures,this));
						colBox->setPosition(0.f,0.f);
						colBox->setCollisionBox(sf::FloatRect(rect.left,rect.top,rect.width,rect.height));
						colBox->enableCollision(true);
						addNode(&colBox,Object);
					}
					else if(object["properties"].at(0)["value"] == "enemyTurn")
					{
						std::unique_ptr<Actor> colBox(new Actor(sfx,textures,this));
						colBox->setPosition(0.f,0.f);
						colBox->setCollisionBox(sf::FloatRect(rect.left,rect.top,rect.width,rect.height));
						colBox->enableCollision(true);
						colBox->setCategory(Category::EnemyBlock | Category::Actor);
						addNode(&colBox,Object);
					}
					else if(object["properties"].at(0)["value"] == "originTP")
					{
						std::unique_ptr<Actor> colBox(new Actor(sfx,textures,this));
						colBox->setPosition(0.f,0.f);
						colBox->setCollisionBox(sf::FloatRect(rect.left,rect.top,rect.width,rect.height));
						colBox->enableCollision(true);
						colBox->setCategory(Category::OriginTP | Category::Actor);
						addNode(&colBox,Object);
					}
				}
			}
		}
	}
}

sf::RenderWindow* World::getWindow()
{
	return &window;
}

float World::getViewScale()
{
	return viewScale;
}

void World::loadResources()
{
}

void World::changeWorld(World* newWorld)
{
	song.stop();
	currentWorld->reset(newWorld);
	//delete this;
}

