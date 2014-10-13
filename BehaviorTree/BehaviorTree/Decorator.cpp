#include "Decorator.h"


Decorator::Decorator(Node* child) :
	_child(child)
{
	_child->setParent(this);
}


Decorator::~Decorator()
{
	if (_child != nullptr)
	{
		_child->setParent(nullptr);
		delete _child;
		_child = nullptr;
	}
}
