#include "Assert.h"
#include "Composite.h"


Composite::Composite()
{
}


Composite::~Composite()
{
	while (!_children.empty())
	{
		Node* child = _children.back();
		child->setParent(nullptr);
		delete child;
		_children.pop_back();
	}
}

void Composite::addChild(Node* child)
{
	child->setParent(this);
	_children.push_back(child);
}

Node& Composite::operator[](size_t idx) const
{
	ASSERT_MSG(idx < _children.size(), "Index out of range");
	return *_children[idx];
}
