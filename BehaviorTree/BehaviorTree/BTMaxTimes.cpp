#include "BTMaxTimes.h"

BTMaxTimes::BTMaxTimes(BTNode* parent, int maxTimes) : 
	BTCondition(parent), _maxTimes(maxTimes)
{ 
}

BTMaxTimes::~BTMaxTimes()
{

}

Status BTMaxTimes::execute()
{
	if (_maxTimes <= _count++)
	{
		return Status::SUCCEDED;
	}

	return Status::RUNNING;
}
