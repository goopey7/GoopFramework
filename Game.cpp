//Copyright Sam Collier 2022

#include "Game.h"

void Game::initWindow()
{
	std::ifstream ifs("config/window.cfg");
	sf::VideoMode windowSize(800,600);
	bool vSyncEnabled = false;
	if(ifs.is_open() && ifs.good())
	{
		std::getline(ifs,title);
		ifs >> windowSize.width >> windowSize.height;
		ifs >> vSyncEnabled;
	}
	if(!ifs.good())
	{
		windowSize = sf::VideoMode(800,600);
		vSyncEnabled = false;
	}
	ifs.close();
	std::filesystem::create_directory("config");
	std::ofstream ofs("config/window.cfg",std::ofstream::out);
	ofs << title << '\n';
	ofs << std::to_string(windowSize.width) << " " << std::to_string(windowSize.height) << '\n';
	ofs << std::to_string(vSyncEnabled);
	ofs.close();
	window = new sf::RenderWindow(windowSize,title);
	window->setVerticalSyncEnabled(vSyncEnabled);
}

Game::Game()
{ 
	initWindow();
}

Game::~Game()
{
	delete window;
}

void Game::handleEvents()
{
	sf::Event ev;
	while(window->pollEvent(ev))
	{
		if(ev.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update(const float dt)
{
}

void Game::fixedUpdate(const float dt)
{
}

void Game::render()
{
	window->clear();

	window->display();
}

void Game::run()
{
	const sf::Time TimePerFixedUpdate = sf::seconds(1.f/TicksPerSec);
	sf::Clock timer;
	sf::Time prevTime = sf::Time::Zero;
	sf::Time timeBetweenTicks = sf::Time::Zero;
	
	// GAME LOOP
	while(window->isOpen())
	{
		// get the time
		sf::Time currentTime = timer.getElapsedTime();
		sf::Time dt = currentTime - prevTime;
		timeBetweenTicks += dt;
		prevTime = currentTime;

		// Realtime Events
		handleEvents();
		update(dt.asSeconds());

		// Fixed Time Events
		while(timeBetweenTicks >= TimePerFixedUpdate)
		{
			fixedUpdate(TimePerFixedUpdate.asSeconds());
			// subtract a fixedUpdate worth of ticks
			timeBetweenTicks-=TimePerFixedUpdate;
		}

		// Rendering
		render();
	}
}

