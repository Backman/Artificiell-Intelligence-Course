#include "Sequence.h"


Sequence::Sequence()
{
}


Sequence::~Sequence()
{
}

Status Sequence::execute()
{
	for (int i = 0; i < _children.size(); ++i)
	{
		Status status = _children[i]->tick();

		if (status != Status::SUCCESS)
		{
			return status;
		}
	}

	return Status::SUCCESS;
}
