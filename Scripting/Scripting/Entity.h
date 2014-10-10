#pragma once

#include <SFML\Graphics.hpp>
#include <luacppinterface.h>

class Entity
{
public:

	Entity(const std::string& luaFile);
	~Entity();

	void tick(float delta);
	void render(sf::Window* window);

	void recompile();

protected:
	Lua _lua;

	LuaFunction<void(float)>* _tickFunc;
	LuaFunction<void(sf::Window*)>* _renderFunc;

	std::string _luaFile;
};