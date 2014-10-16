#include "BSPNode.h"

BSPNode::BSPNode(int x, int y, int width, int height) :
	_bounds(sf::IntRect(x, y, width, height)),
	_minSize(50),
	_leftChild(nullptr), _rightChild(nullptr)
{
	_r = Utility::randomFloatRange() * 255;
	_g = Utility::randomFloatRange() * 255;
	_b = Utility::randomFloatRange() * 255;
}

BSPNode::~BSPNode()
{

}

bool BSPNode::splitNode()
{
	if (_leftChild != nullptr || _rightChild != nullptr)
	{
		return false;
	}

	bool splitHorizontal = Utility::randomFloatRange() > 0.5f;

	if (_bounds.width > _bounds.height && _bounds.height / _bounds.width >= 0.05)
	{
		splitHorizontal = false;
	}
	else if (_bounds.height > _bounds.width && _bounds.width / _bounds.height >= 0.05)
	{
		splitHorizontal = true;
	}

	int max = (splitHorizontal ? _bounds.height : _bounds.width) - _minSize;
	if (max <= _minSize)
	{
		return false;
	}

	int split = Utility::randomIntRange(_minSize, max);
	if (splitHorizontal)
	{
		_leftChild = new BSPNode(_bounds.left, _bounds.top, _bounds.width, split);
		_rightChild = new BSPNode(_bounds.left, _bounds.top + split, _bounds.width, _bounds.height - split);
	}
	else
	{
		_leftChild = new BSPNode(_bounds.left, _bounds.top, split, _bounds.height);
		_rightChild = new BSPNode(_bounds.left + split, _bounds.top, _bounds.width - split, _bounds.height);
	}

	return true;
}

void BSPNode::createRooms()
{
	bool ready = true;
	if (_leftChild != nullptr)
	{
		ready = false;
		_leftChild->createRooms();
	}
	if (_rightChild != nullptr)
	{
		ready = false;
		_rightChild->createRooms();
	}

	if (ready)
	{
		sf::Vector2i size;
		sf::Vector2i pos;

		size = sf::Vector2i(Utility::randomIntRange(_bounds.width * 0.2f, _bounds.width - 10), Utility::randomIntRange(_bounds.height * 0.2f, _bounds.height - 10));
		pos = sf::Vector2i(Utility::randomIntRange(5, _bounds.width - size.x - 5), Utility::randomIntRange(5, _bounds.height - size.y - 5));

		_room = sf::IntRect(_bounds.left + pos.x, _bounds.top + pos.y, size.x, size.y);
	}
}

void BSPNode::render(sf::RenderWindow* window)
{
	sf::RectangleShape shape(sf::Vector2f((float)_bounds.width, (float)_bounds.height));
	shape.setPosition(_bounds.left, _bounds.top);

	shape.setFillColor(sf::Color(_r, _g, _b, 255));

	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5.0f);

	sf::RectangleShape room(sf::Vector2f((float)_room.width, (float)_room.height));
	room.setPosition(_room.left, _room.top);
	room.setFillColor(sf::Color::White);


	//window->draw(shape);
	window->draw(room);
}

const sf::IntRect& BSPNode::getBounds() const
{
	return _bounds;
}

const sf::IntRect& BSPNode::getRoom() const
{
	return _room;
}

BSPNode* BSPNode::getLeftChild() const
{
	return _leftChild;
}

BSPNode* BSPNode::getRightChild() const
{
	return _rightChild;
}

