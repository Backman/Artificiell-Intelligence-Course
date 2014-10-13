#pragma once
#include "Composite.h"
class Sequence :
	public Composite
{
public:
	Sequence();
	~Sequence();

protected:
	virtual Status execute() override;
};

