#pragma once

#include <SFML\Graphics.hpp>

class Map;
class MapGenerator;

class Engine
{
public:
	Engine(int windowWidth, int windowHeight, const std::string& title);
	~Engine();

	void run();
	bool init();

	void setGenerator(MapGenerator* generator);

private:
	void mainLoop();
	void tick();
	void render();
	void processEvent();

	bool _initialized;
	std::string _title;
	Map* _currentMap;
	sf::RenderWindow* _window;
	sf::VideoMode _videoMode;
	MapGenerator* _generator;
};

