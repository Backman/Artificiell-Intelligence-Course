#include <luacppinterface.h>
#include <iostream>
#include <fstream>
#include <streambuf>

#include <SFML\Graphics.hpp>

#include "Entity.h"

int main()
{
	std::ifstream file("Config.lua");
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	Lua lua;

	lua.LoadStandardLibraries();

	lua.RunScript(script);

	LuaTable global = lua.GetGlobalEnvironment();
	int width = global.Get<int>("width");
	int height = global.Get<int>("height");
	std::string title = global.Get<std::string>("title");


	sf::RenderWindow window(sf::VideoMode(width, height), title);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window.setFramerateLimit(60);

	sf::Clock deltaClock;

	std::string entityFile = "Player.lua";
	Entity e(entityFile);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Event::KeyEvent key = event.key;

			switch (key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;

			case sf::Keyboard::F:
				e.recompile();
				break;
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		float delta = deltaClock.restart().asSeconds();

		e.tick(delta);

		window.clear();
		e.render(&window);
		window.draw(shape);
		window.display();
	}

	return 0;
}