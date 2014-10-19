#include "Engine.h"
#include "Utility.h"


Engine::Engine(int windowWidth, int windowHeight, const std::string& windowTitle) :
	_videoMode(sf::VideoMode(windowWidth, windowHeight))
{
}


Engine::~Engine()
{
	Utility::deletePointer<sf::RenderWindow>(_window);
}

bool Engine::init()
{
	_window = new sf::RenderWindow(_videoMode, _windowTitle);

	if (_window == nullptr)
	{
		return false;
	}

	return true;
}

void Engine::run()
{
	if (!init())
	{
		return;
	}

	mainLoop();
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

void Engine::tick()
{

}

void Engine::render()
{
	_window->clear();

	_window->display();
}

void Engine::processEvent()
{
	sf::Event evt;
	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || evt.key.code == sf::Keyboard::Escape)
		{
			_window->close();
		}
	}
}

