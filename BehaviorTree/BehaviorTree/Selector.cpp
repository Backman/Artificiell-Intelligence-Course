#include "Selector.h"


Selector::Selector()
{
}


Selector::~Selector()
{
}

Status Selector::execute()
{
	for (int i = 0; i < _children.size(); ++i)
	{
		Status status = _children[i]->tick();

		if (status != Status::FAILURE)
		{
			return status;
		}
	}

	return Status::SUCCESS;
}
