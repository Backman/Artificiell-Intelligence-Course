#pragma once

#include <SFML\Graphics.hpp>
#include "Utility.h"

class BSPNode
{
public:
	BSPNode(int x, int y, int width, int height);
	~BSPNode();

	bool splitNode();
	void createRooms();

	void render(sf::RenderWindow* window);

	const sf::IntRect& getBounds() const;
	const sf::IntRect& getRoom() const;

	BSPNode* getLeftChild() const;
	BSPNode* getRightChild() const;


private:
	sf::IntRect _bounds;
	sf::IntRect _room;

	BSPNode* _leftChild;
	BSPNode* _rightChild;
	int _minSize;
	int _r, _g, _b;
};

