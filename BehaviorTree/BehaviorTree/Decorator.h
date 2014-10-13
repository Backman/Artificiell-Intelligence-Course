#pragma once
#include "Node.h"
class Decorator :
	public Node
{
public:
	Decorator(Node* child);
	virtual ~Decorator();

protected:
	Node* _child;
};

