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
			if(Collision::ActorVActor(collidingActors[i],collidingActors[j]))
			{
				collidingActors[i]->onCollision();
				collidingActors[j]->onCollision();
			}
			else
			{
				collidingActors[i]->onCollisionExit();
				collidingActors[j]->onCollisionExit();
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

void World::loadFromFile(const char* fileName, TextureHolder& textures)
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

	int textureID = 0;

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
						std::unique_ptr<Actor> tile(new Actor(textures));
						tile->setTexture(textureID-1);
						tile->setPosition(x*tileWidth,y*tileHeight);
						sf::IntRect texRect = sf::IntRect(
									(layout[i]-1)*tileWidth,0,
									tileWidth,tileHeight);
						tile->setTextureRect(texRect);
						addNode(&tile,Object,false);
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
				if(object["properties"].at(0)["value"] == "block")
				{
					std::unique_ptr<Actor> colBox(new Actor(textures));
					colBox->setPosition(0.f,0.f);
					colBox->setCollisionBox(sf::FloatRect(rect.left,rect.top,rect.width,rect.height));
					addNode(&colBox,Object,true);
				}
			}
		}
		
	}
}

