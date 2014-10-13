#include "Assert.h"
#include "BehaviorTree.h"
#include "BTNode.h"

BehaviorTree::BehaviorTree() :
	_root(nullptr)
{
}

BehaviorTree::~BehaviorTree()
{
	if (_root != nullptr)
	{
		delete _root;
		_root = nullptr;
	}
}

void BehaviorTree::init(BTNode* root)
{
	_root = root;
}

Status BehaviorTree::tick()
{
	ASSERT_MSG(_root != nullptr, "Root node is nullptr. Have you called init on the tree?");
	Status s = _root->tick();
	std::cout << "Status: " << StatusStrings[(int)s] << std::endl;
	
	return s;
}
