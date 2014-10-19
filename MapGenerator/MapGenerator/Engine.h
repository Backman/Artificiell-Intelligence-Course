#pragma once

#include <SFML\Graphics.hpp>

class Engine
{
public:
	Engine(int windowWidth, int windowHeight, const std::string& windowTitle);
	~Engine();

	void run();

private:
	bool init();
	void mainLoop();
	void tick();
	void render();
	void processEvent();


	std::string _windowTitle;
	sf::RenderWindow* _window;
	sf::VideoMode _videoMode;
};

