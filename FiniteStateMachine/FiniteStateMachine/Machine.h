#pragma once
#include "State.h"


template<typename T>
class Machine
{
public:
	Machine(T& owner, State<T>& startState) :
		_owner(owner), _currentState(startState)
	{
		addState(startState, owner);
	}

	~Machine()
	{ }

	void addState(State<T>& state, T& owner)
	{
		state.initialize(owner, this);
	}

	void tick()
	{
		_currentState->reason();
		_currentState->tick();
	}

protected:
	T _owner;
	State<T>* _currentState;
};

