#include "Entity.h"
#include <fstream>
#include <streambuf>


Entity::Entity(const std::string& name) :
	_name(name),
	_color(sf::Color::White)
{
}

Entity::~Entity()
{

}

LuaUserdata<Entity> Entity::createEntity(Lua lua, std::string name)
{
	auto userData = lua.CreateUserdata<Entity>(new Entity(name));

	userData.Bind("setPosition", &Entity::setPosition);
	userData.Bind("getX", &Entity::getX);
	userData.Bind("getY", &Entity::getY);
	userData.Bind("setSize", &Entity::setSize);
	userData.Bind("getWidth", &Entity::getWidth);
	userData.Bind("getHeight", &Entity::getHeight);
	userData.Bind("setColor", &Entity::setColor);
	userData.Bind("getName", &Entity::getName);
	userData.Bind("setName", &Entity::setName);

	return userData;
}

void Entity::setPosition(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
}

float Entity::getX() const
{
	return _pos.x;
}

float Entity::getY() const
{
	return _pos.y;
}

void Entity::setSize(float w, float h)
{
	_size.x = w;
	_size.y = h;
}

float Entity::getWidth() const
{
	return _size.x;
}

float Entity::getHeight() const
{
	return _size.y;
}


void Entity::setName(std::string name)
{
	_name = name;
}

std::string Entity::getName() const
{
	return _name;
}

void Entity::setColor(float r, float g, float b)
{
	_color.r = r * 255;
	_color.g = g * 255;
	_color.b = b * 255;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape s(_size);
	s.setPosition(_pos);
	s.setFillColor(_color);

	target.draw(s, states);
}
