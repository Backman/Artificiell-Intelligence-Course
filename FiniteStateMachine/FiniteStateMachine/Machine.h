#pragma once
#include <map>
#include <memory>
#include "State.h"

class Machine
{
public:
	Machine(std::shared_ptr<State> startState) :
		 _currentState(startState)
	{
		addState(startState);
	}

	~Machine()
	{
		_states.clear();
	}

	void addState(std::shared_ptr<State> state)
	{
		state->initialize(this);
		_states[state->getName()] = state;
	}

	void setState(const std::string& stateName)
	{
		if (stateName != _currentState->getName())
		{
			_currentState->exit();
			_currentState = _states[stateName];
			_currentState->enter();
		}
	}

	void tick()
	{
		_currentState->tick();
	}

	State& getCurrentState() const { return *_currentState.get(); }

protected:
	std::shared_ptr<State> _currentState;
	std::map<std::string, std::shared_ptr<State>> _states;
};

