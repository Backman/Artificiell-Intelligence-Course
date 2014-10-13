#pragma once

class BTNode;
enum class Status;

class BehaviorTree
{
public:
	BehaviorTree();
	~BehaviorTree();

	void init(BTNode* root);

	Status tick();

private:
	BTNode* _root;
};

