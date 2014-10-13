#pragma once

enum class Status
{
	INVALID,
	SUCCESS,
	FAILURE,
	RUNNING,
	ERROR
};

class Node
{
public:
	Node() :
		_status(Status::INVALID)
	{ }

	virtual ~Node()
	{ }

	virtual void setParent(Node* parent)
	{
		_parent = parent;
	}

	virtual Status tick()
	{
		if (_status == Status::INVALID)
		{
			init();
		}

		_status = execute();

		if (_status != Status::RUNNING)
		{
			terminate();
		}

		return _status;
	}

protected:
	virtual void init() { }
	virtual void terminate() { }
	virtual Status execute() = 0;

	Status _status;
	Node* _parent;
};

