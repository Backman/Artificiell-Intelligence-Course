#include "BTSequence.h"


BTSequence::BTSequence(BTNode* parent) :
	BTCompositeNode(parent)
{
}


BTSequence::~BTSequence()
{
}

Status BTSequence::execute()
{
	NodeList::iterator currentChild = _children.begin();

	for (auto& child : _children)
	{
		Status s = child->tick();

		if (s != Status::SUCCEDED)
		{
			return s;
		}
	}

	return Status::SUCCEDED;
}
