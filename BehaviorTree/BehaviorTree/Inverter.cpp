#include "Inverter.h"


Inverter::Inverter(Node* child) : 
	Decorator(child)
{
}


Inverter::~Inverter()
{
}

Status Inverter::execute()
{
	Status s = _child->tick();

	if (s == Status::SUCCESS)
	{
		return Status::FAILURE;
	}
	else if (s == Status::FAILURE)
	{
		return Status::SUCCESS;
	}
	
	return s;
}