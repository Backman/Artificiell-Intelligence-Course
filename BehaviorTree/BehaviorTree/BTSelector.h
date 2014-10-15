#pragma once
#include "BTCompositeNode.h"
class BTSelector :
	public BTCompositeNode
{
public:
	BTSelector(BTNode* parent);
	~BTSelector();

protected:
	Status execute() override;
};

