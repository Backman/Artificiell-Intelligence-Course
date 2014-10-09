#include <luacppinterface.h>
#include <iostream>
#include <fstream>
#include <streambuf>

#include <SFML\Graphics.hpp>

int main()
{
	std::ifstream file("Config.lua");
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::ifstream file2("Player.lua");
	std::string script2((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());
	

	Lua lua;
	Lua lua2;

	lua.RunScript(script);

	lua2.LoadStandardLibraries();
	lua2.RunScript(script2);

	file2.close();

	int width = lua.GetGlobalEnvironment().Get<int>("width");
	int height = lua.GetGlobalEnvironment().Get<int>("height");
	std::string title = lua.GetGlobalEnvironment().Get<std::string>("title");

	LuaTable global = lua2.GetGlobalEnvironment();

	auto updateFunc = global.Get<LuaFunction<void(float)>>("update");


	sf::RenderWindow window(sf::VideoMode(width, height), title);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window.setFramerateLimit(60);

	sf::Clock deltaClock;

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
				file2.open("Player.lua");
				script2 = std::string((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());
				lua2.RunScript(script2);
				updateFunc = global.Get<LuaFunction<void(float)>>("update");
				file2.close();
				break;
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		float delta = deltaClock.restart().asSeconds();

		updateFunc.Invoke(delta);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}