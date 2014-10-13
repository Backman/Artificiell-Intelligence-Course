#pragma once
#include "Composite.h"
class Selector :
	public Composite
{
public:
	Selector();
	~Selector();

protected:
	virtual Status execute() override;
};

