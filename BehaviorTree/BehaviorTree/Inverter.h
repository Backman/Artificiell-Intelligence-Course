#pragma once

#include "Decorator.h"


class Inverter :
	public Decorator
{
public:
	Inverter(Node* child);
	~Inverter();

protected:
	virtual Status execute() override;
};

