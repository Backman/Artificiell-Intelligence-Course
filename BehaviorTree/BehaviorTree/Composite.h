#pragma once

#include <vector>
#include "Node.h"

class Composite :
	public Node
{
public:
	Composite();
	virtual ~Composite();

	void addChild(Node* child);

	Node& operator[](size_t idx) const;

protected:
	std::vector<Node*> _children;
};

