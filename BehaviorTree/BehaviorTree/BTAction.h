#pragma once
#include "BTTaskNode.h"
class BTAction :
	public BTTaskNode
{
public:
	BTAction(BTNode* parent) : BTTaskNode(parent)
	{ }
	virtual ~BTAction()
	{ }
};

