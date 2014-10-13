#include "BTSelector.h"

BTSelector::BTSelector(BTNode* parent) : 
	BTCompositeNode(parent)
{
}


BTSelector::~BTSelector()
{
}

Status BTSelector::execute()
{
	NodeList::iterator currentChild = _children.begin();
	
	std::cout << "Execute selector..." << std::endl;
	for (auto& child : _children)
	{
		Status s = child->tick();

		if (s != Status::FAILURE)
		{
			return s;
		}
	}

	return Status::FAILURE;
}