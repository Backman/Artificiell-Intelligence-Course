#pragma once

#include "State.h"
#include <stack>
#include <functional>

class StackFSM
{
public:
	StackFSM()
	{
	}

	~StackFSM() { }

	void tick()
	{
		State* f = getState();
		if (f != nullptr)
		{
			f->tick();
		}
	}

	void pushState(State state)
	{
		State* s = getState();

		if (s == nullptr || *s != state)
		{
			_funcStack.push(state);
		}
	}
	
	void popState()
	{
		_funcStack.pop();
	}
	
	State* getState()
	{
		return _funcStack.size() > 0 ? &_funcStack.top() : nullptr;
	}

private:
	std::stack<State> _funcStack;
};