#include "Entity.h"
#include <fstream>
#include <streambuf>

Entity::Entity(const std::string& luaFile) :
	_luaFile(luaFile)
{
	std::ifstream file(luaFile);
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	_lua.LoadStandardLibraries();
	_lua.RunScript(script);
	auto global = _lua.GetGlobalEnvironment();

	_tickFunc = new LuaFunction<void(float)>(global.Get<LuaFunction<void(float)>>("tick"));
	_renderFunc = new LuaFunction<void(sf::Window*)>(global.Get<LuaFunction<void(sf::Window*)>>("render"));
}

Entity::~Entity()
{
	if (_tickFunc != nullptr)
	{
		delete _tickFunc;
		_tickFunc = nullptr;
	}
	if (_renderFunc != nullptr)
	{
		delete _renderFunc;
		_renderFunc = nullptr;
	}
}

void Entity::recompile()
{
	std::ifstream file(_luaFile);
	std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	_lua.RunScript(script);
	auto global = _lua.GetGlobalEnvironment();

	_tickFunc = new LuaFunction<void(float)>(global.Get<LuaFunction<void(float)>>("tick"));
	_renderFunc = new LuaFunction<void(sf::Window*)>(global.Get<LuaFunction<void(sf::Window*)>>("render"));
}

void Entity::tick(float delta)
{
	_tickFunc->Invoke(delta);
}

void Entity::render(sf::Window* window)
{
	_renderFunc->Invoke(window);
}