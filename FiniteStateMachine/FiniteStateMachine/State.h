#pragma once

template<typename T>
class Machine;

template<typename T>
class State
{
public:
	State()
	{ }

	virtual ~State()
	{ }

	virtual void initialize(T& owner, Machine<T>* machine)
	{
		_owner = owner;
		_machine = machine;
	}

	virtual void tick() = 0;
	virtual void reason() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

protected:
	T _owner;
	Machine<T>* _machine;
};

