#include "BSPDungeon.h"
#include "BSPNode.h"

BSPDungeon::BSPDungeon()
{
}


BSPDungeon::~BSPDungeon()
{
	destroyNodes();
}

void BSPDungeon::destroyNodes()
{
	while (!_nodes.empty())
	{
		delete _nodes.back();
		_nodes.pop_back();
	}
}

void BSPDungeon::addNode(BSPNode* node)
{
	_nodes.push_back(node);
}

void BSPDungeon::generate(int width, int height, int iterations)
{
	_width = width;
	_heigth = height;
	
	const int MAX_NODE_SIZE = 60;

	BSPNode* root = new BSPNode(0, 0, _width, _heigth);
	addNode(root);

	bool split = true;

	BSPNode* node;

	int iteration = 0;
	while (iteration < iterations)
	{
		std::vector<BSPNode*> nodes(_nodes.size());
		for (int i = 0; i < _nodes.size(); ++i)
		{
			nodes[i] = _nodes[i];
		}
		iteration++;
		split = false;
		for (int n = 0; n < nodes.size(); ++n)
		{
			node = _nodes[n];
			if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
			{
				if (node->getBounds().width < MAX_NODE_SIZE || node->getBounds().height < MAX_NODE_SIZE || Utility::randomFloatRange() > 0.25)
				{
					if (node->splitNode())
					{
						addNode(node->getLeftChild());
						addNode(node->getRightChild());
					}
				}
			}
		}
	}

	root->createRooms();
}

void BSPDungeon::render(sf::RenderWindow* window)
{
	for (auto& node : _nodes)
	{
		node->render(window);
	}
}
