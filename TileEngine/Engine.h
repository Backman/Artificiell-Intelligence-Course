#pragma once

#include <SFML\Graphics.hpp>
#include "ImageManager.h"

class Camera;
class Level;

class Engine
{
public:
	Engine(int width, int height, int tileSize, int bitsPerPixel = 32);
	~Engine();

	void start();

private:
	void mainLoop();
	bool init();
	void tick();
	void render();

	void processInput();

	void loadImages();

	sf::RenderWindow* _window;
	sf::VideoMode videoMode;
	ImageManager _imageManager;

	Camera* _camera;
	Level* _currentLevel;

	bool _mouseDown;
	int _tileSize;
};

