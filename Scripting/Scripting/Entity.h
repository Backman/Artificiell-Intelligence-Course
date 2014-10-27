#pragma once

#include <SFML\Graphics.hpp>
#include "luacppinterface.h"


class Entity : public sf::Drawable
{
public:
	Entity(const std::string& name);
	~Entity();

	void tick(float dt);

	void setPosition(float x, float y);
	float getX() const;
	float getY() const;

	void setSize(float w, float h);
	float getWidth() const;
	float getHeight() const;

	void setName(std::string name);
	std::string getName() const;

	void setColor(float r, float g, float b);

	static LuaUserdata<Entity> createEntity(Lua lua, std::string name);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::string _name;
	sf::Vector2f _pos;
	sf::Vector2f _size;
	sf::Color _color;
};

