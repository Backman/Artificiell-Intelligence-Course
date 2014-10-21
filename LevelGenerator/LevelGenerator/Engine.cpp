#include <iostream>
#include "Engine.h"
#include "Utility.h"
#include "Assert.h"
#include "Map.h"
#include "MapGenerator.h"

Engine::Engine(int windowWidth, int windowHeight, const std::string& title) :
	_videoMode(windowWidth, windowHeight),
	_initialized(false),
	_title(title)
{
}

Engine::~Engine()
{
	Utility::deletePointer<sf::RenderWindow>(_window);
	Utility::deletePointer<Map>(_currentMap);
}

void Engine::run()
{
	ASSERT_MSG(init(), "Failed to initialize Engine...");

	mainLoop();
}

void Engine::setGenerator(MapGenerator* generator)
{
	_generator = generator;
}

bool Engine::init()
{
	if (!_initialized)
	{
		_window = new sf::RenderWindow(_videoMode, _title);

		if (_window == nullptr)
		{
			return false;
		}

		if (_generator == nullptr)
		{
			std::cerr << "No generator... Creating basic grid" << std::endl;
			_currentMap = new Map;
			_currentMap->initMap(50, 50, 10);
		}

		_initialized = true;
	}

	return true;
}

void Engine::mainLoop()
{
	while (_window->isOpen())
	{
		processEvent();
		tick();
		render();
	}
}
#include "TKGenerator.h"
void Engine::tick()
{
	((TKGenerator*)_generator)->seperate();
}

void Engine::render()
{
	_window->clear();

	if (_currentMap != nullptr)
	{
		_currentMap->render(_window);
	}
	else if (_generator != nullptr)
	{
		_generator->render(_window);
	}

	_window->display();
}

void Engine::processEvent()
{
	sf::Event evt;

	while (_window->pollEvent(evt))
	{
		sf::Event::KeyEvent key = evt.key;
		sf::Event::EventType type = evt.type;

		if (type == sf::Event::Closed || key.code == sf::Keyboard::Escape)
		{
			_window->close();
		}

		if (key.code == sf::Keyboard::R)
		{
			int cellCount = 80;
			int tileSize = 8;
			int minCellSize = 4;
			int maxCellSize = 10;
			int minCellThreshold = 5;
			int maxCellThrehsold = 7;

			((TKGenerator*)_generator)->initGenerator(cellCount, tileSize, minCellSize, maxCellSize, minCellThreshold, maxCellThrehsold);
		}
	}
}
