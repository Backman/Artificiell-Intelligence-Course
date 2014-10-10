#pragma once

#include <iostream>
#include <string>

class Machine;

class State
{
public:
	State(std::string name) :
		_name(name), _isEntered(false)
	{ }

	virtual ~State()
	{ }

	virtual void initialize(Machine* machine)
	{
		_machine = machine;
	}

	virtual void tick() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	bool operator==(const State& rhs) const
	{
		return _name == rhs._name;
	}

	bool operator!=(const State& rhs) const
	{
		return !(*this == rhs);
	}

	std::string getName() const { return _name; }

protected:
	Machine* _machine;
	std::string _name;

	bool _isEntered;
};

