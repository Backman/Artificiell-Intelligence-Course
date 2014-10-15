#pragma once

#include <vector>
#include "BTNode.h"

class BTCompositeNode :
	public BTNode
{
public:
	BTCompositeNode(BTNode* parent) :
		BTNode(parent)
	{
	}


	virtual ~BTCompositeNode()
	{
		while (!_children.empty())
		{
			delete _children.back();
			_children.pop_back();
		}
	}

	void addChild(BTNode* child)
	{
		_children.push_back(child);
	}

protected:
	typedef std::vector<BTNode*> NodeList;
	NodeList _children;
};

