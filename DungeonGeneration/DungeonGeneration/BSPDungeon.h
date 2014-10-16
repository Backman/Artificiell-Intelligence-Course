#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>

#include "Utility.h"

class BSPNode;

class BSPDungeon
{
public:
	BSPDungeon();
	~BSPDungeon();

	void generate(int width, int height, int iterations);

	void addNode(BSPNode* node);

	void render(sf::RenderWindow* window);

private:
	void destroyNodes();

	

	int _width, _heigth;
	std::vector<BSPNode*> _nodes;
};

