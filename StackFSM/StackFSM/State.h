#pragma once

#include <string>
#include <functional>
#include <iostream>

class Entity;

class State
{
	typedef std::function<void()> TickFunc;
public:
	State(const std::string& name, TickFunc tickFunc) :
		_tickFunc(tickFunc),
		_name(name)
	{
	}
	~State() { }

	void tick()
	{
		_tickFunc();
	}

	bool operator!=(const State& other) const
	{
		return _name != other._name;
	}

private:
	TickFunc _tickFunc;
	std::string _name;
};