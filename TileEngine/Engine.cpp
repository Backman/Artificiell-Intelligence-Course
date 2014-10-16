#include "Engine.h"
#include "Tile.h"
#include "Camera.h"
#include "Level.h"
#include "Assert.h"

template<class T>
void deletePointer(T* p)
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}

Engine::Engine(int width, int height, int tileSize, int bitsPerPixel) : 
	videoMode(width, height, bitsPerPixel),
	_mouseDown(false), _tileSize(tileSize)
{
	_imageManager.setTileSize(tileSize);
}


Engine::~Engine()
{
	deletePointer<sf::RenderWindow>(_window);
	deletePointer<Camera>(_camera);
	deletePointer<Level>(_currentLevel);
}

bool Engine::init()
{
	_window = new sf::RenderWindow(videoMode, "Dungeon Generator");

	if (_window == nullptr)
	{
		return false;
	}

	loadImages();

	_currentLevel = new Level;
	_currentLevel->initLevel(80, 80, _imageManager);

	_camera = new Camera(videoMode.width, videoMode.height, 0.1f);

	return true;
}

void Engine::render()
{
	int camOffsetX, camOffsetY;

	_window->clear();

	sf::IntRect bounds = _camera->getTileBounds(_tileSize);

	camOffsetX = _camera->getTileOffset(_tileSize).x;
	camOffsetY = _camera->getTileOffset(_tileSize).y;
	
	_currentLevel->render(bounds, _tileSize, camOffsetX, camOffsetY, _window);

	_window->display();
}

void Engine::processInput()
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

		if ((type == sf::Event::MouseButtonPressed) && !_mouseDown)
		{
			sf::Mouse mouse;

			int x = _camera->getPosition().x + mouse.getPosition(*_window).x;
			int y = _camera->getPosition().y + mouse.getPosition(*_window).y;

			_camera->goToCenter(x, y);
			_mouseDown = true;
		}
		if (type == sf::Event::MouseButtonReleased)
		{
			_mouseDown = false;
		}
	}
}

void Engine::tick()
{
	_camera->tick();
}

void Engine::mainLoop()
{
	while (_window->isOpen())
	{
		processInput();
		tick();
		render();
	}
}

void Engine::start()
{
	ASSERT_MSG(init(), "Failed to initialize the Engine...");

	mainLoop();
}

void Engine::loadImages()
{
	sf::Image image1;
	image1.loadFromFile("sprite1.png");
	sf::Image image2;
	image2.loadFromFile("sprite2.png");

	_imageManager.addImage(image1, 0);
	_imageManager.addImage(image2, 1);
}