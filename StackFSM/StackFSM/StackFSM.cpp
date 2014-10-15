//#include "StackFSM.h"
//#include "State.h"
//
//StackFSM::StackFSM()
//{
//}
//
//
//StackFSM::~StackFSM()
//{
//}
//
//void StackFSM::tick()
//{
//	State* s = getState();
//
//	if (s != nullptr)
//	{
//		s->tick();
//	}
//}
//
//void StackFSM::pushState(State* state)
//{
//	state->enter();
//	_stack.push(state);
//}
//
//void StackFSM::popState()
//{
//	State* state = _stack.top();
//	state->exit();
//	delete state;
//	_stack.pop();
//}
//
//State* StackFSM::getState()
//{
//	return _stack.size() > 0 ? _stack.top() : nullptr;
//}
