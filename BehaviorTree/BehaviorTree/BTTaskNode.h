#pragma once
#include "BTNode.h"
class BTTaskNode :
	public BTNode
{
public:
	BTTaskNode(BTNode* parent) : BTNode(parent)
	{ }
	~BTTaskNode()
	{ }
};

