#pragma once
#include "BTCompositeNode.h"
class BTSequence :
	public BTCompositeNode
{
public:
	BTSequence(BTNode* parent);
	~BTSequence();

protected:
	Status execute() override;
};

