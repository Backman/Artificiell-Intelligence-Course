#include "Entity.h"
#include <functional>
#include <fstream>
#include <streambuf>
#include <iostream>

class Input
{
public:
	bool isPressed(int key)
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 640), "Scripting");

	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	lua.LoadStandardLibraries();

	std::ifstream file("Entity.lua");
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	auto keyPressed = lua.CreateFunction<bool(int)>([&](int key)
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
	});

	global.Set("keyPressed", keyPressed);

	global.Set("A", (int)sf::Keyboard::A);
	global.Set("D", (int)sf::Keyboard::D);
	global.Set("W", (int)sf::Keyboard::W);
	global.Set("S", (int)sf::Keyboard::S);

	global.Set("Up", (int)sf::Keyboard::Up);
	global.Set("Down", (int)sf::Keyboard::Down);
	global.Set("Left", (int)sf::Keyboard::Left);
	global.Set("Right", (int)sf::Keyboard::Right);

	auto entity = Entity::createEntity(lua, "Entity_01");
	global.Set("entity", entity);

	lua.RunScript(script);

	auto tick = global.Get<LuaFunction<void(float)>>("tick");
	auto init = global.Get<LuaFunction<void()>>("init");
	
	init.Invoke();

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed || evt.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (evt.key.code == sf::Keyboard::R)
			{
				file.open("Entity.lua");
				script = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

				lua.RunScript(script);

				tick = global.Get<LuaFunction<void(float)>>("tick");

				file.close();
			}
		}


		float dt = deltaClock.restart().asSeconds();

		tick.Invoke(dt);

		window.clear();
		
		window.draw(*entity.GetPointer());

		window.display();
	}

	return 0;
}