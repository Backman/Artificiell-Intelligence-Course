#pragma once
#include "BTTaskNode.h"
class BTCondition :
	public BTTaskNode
{
public:
	BTCondition(BTNode* parent) : BTTaskNode(parent)
	{ }
	virtual ~BTCondition()
	{ }
};

