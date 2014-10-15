#pragma once
#include "BTNode.h"
class BTDecoratorNode :
	public BTNode
{
public:
	BTDecoratorNode(BTNode* parent, BTNode* child) :
		BTNode(parent), _child(child)
	{ }
	virtual ~BTDecoratorNode()
	{ 
		if (_child != nullptr)
		{
			delete _child;
			_child = nullptr;
		}
	}

protected:
	BTNode* _child;
};

