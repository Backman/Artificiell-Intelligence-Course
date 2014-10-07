#include <luacppinterface.h>
#include <iostream>
#include <fstream>
#include <streambuf>

#include <SFML\Graphics.hpp>

int main()
{
	std::ifstream file("Config.lua");
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	Lua lua;
	lua.RunScript(script);

	int width = lua.GetGlobalEnvironment().Get<int>("width");
	int height = lua.GetGlobalEnvironment().Get<int>("height");
	std::string title = lua.GetGlobalEnvironment().Get<std::string>("title");


	sf::RenderWindow window(sf::VideoMode(width, height), title);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}