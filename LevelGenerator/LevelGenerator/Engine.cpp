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

void Engine::run(MapGenerator* generator)
{
	ASSERT_MSG(init(generator), "Failed to initialize Engine...");

	mainLoop();
}

bool Engine::init(MapGenerator* generator)
{
	if (!_initialized)
	{
		_window = new sf::RenderWindow(_videoMode, _title);

		if (_window == nullptr)
		{
			return false;
		}

		if (generator != nullptr)
		{
			_generator = generator;
			//_generator->generate();
			//_currentMap = generator->generate();
		}
		else
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
	}
}
