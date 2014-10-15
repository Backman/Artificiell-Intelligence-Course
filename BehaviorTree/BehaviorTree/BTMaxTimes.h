#pragma once
#include "BTCondition.h"
class BTMaxTimes :
	public BTCondition
{
public:
	BTMaxTimes(BTNode* parent, int maxTimes);
	~BTMaxTimes();

protected:
	Status execute() override;

	int _count;
	int _maxTimes;
};

