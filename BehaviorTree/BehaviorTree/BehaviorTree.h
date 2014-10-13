#pragma once

class Node;

class BehaviorTree
{
public:
	BehaviorTree(Node* root);
	~BehaviorTree();

	void tick();

private:
	Node* _root;
};

