#include "Cell.h"


Cell::Cell(int x, int y, int width, int height, int idx) :
	_index(idx)
{
	_rect.left = x + (width / 2);
	_rect.top = y + (height / 2);
	_rect.width = width;
	_rect.height = height;

	_shape.setSize(sf::Vector2f(width, height));

	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(1.0f);
	_shape.setFillColor(sf::Color::Blue);
}


Cell::~Cell()
{
}

void Cell::render(sf::RenderWindow* window)
{
	sf::CircleShape c(1.0f);
	c.setFillColor(sf::Color::Red);
	c.setPosition(getPosition());

	_shape.setPosition(sf::Vector2f(_rect.left, _rect.top));
	window->draw(_shape);
	window->draw(c);
}

sf::Vector2f Cell::getPosition() const
{
	return sf::Vector2f(_rect.left + (_rect.width / 2), _rect.top + (_rect.height / 2));
}

void Cell::setPosition(sf::Vector2f pos)
{
	_rect.left = pos.x - (_rect.width / 2);
	_rect.top = pos.y - (_rect.height / 2);
}

void Cell::setPosition(int x, int y)
{
	_rect.left = (float)x - (float)(_rect.width / 2);
	_rect.top = (float)y - (float)(_rect.height / 2);
}

void Cell::setPosition(float x, float y)
{
	_rect.left = x - (_rect.width / 2);
	_rect.top = y - (_rect.height / 2);
}

bool Cell::intersects(const Cell& other) const
{
	return _rect.intersects(other._rect);
}

void Cell::setIndex(int index)
{
	_index = index;
}

bool Cell::operator==(const Cell& rhs) const
{
	return _index == rhs._index;
}

bool Cell::operator!=(const Cell& rhs) const
{
	return _index != rhs._index;
}
