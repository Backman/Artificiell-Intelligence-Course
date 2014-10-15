#pragma once
#include <iostream>

enum class Status
{
	INVALID,
	SUCCEDED,
	FAILURE,
	RUNNING,
	ERROR
};

static const char* StatusStrings[] =
{
	"INVALID",
	"SUCCEDED",
	"FAILURE",
	"RUNNING",
	"ERROR"
};

class BTNode
{
public:
	BTNode() :
		_parent(nullptr)
	{
	}

	BTNode(BTNode* parent) :
		_parent(parent)
	{
	}

	virtual ~BTNode()
	{

	}

	Status tick()
	{
		if (_status == Status::INVALID)
		{
			init();
		}

		_status = execute();

		if (_status != Status::RUNNING)
		{
			terminate(_status);
		}

		return _status;
	}

protected:
	virtual Status execute() = 0;
	virtual void init(){ }
	virtual void terminate(Status s) { }

	BTNode* _parent;
	Status _status;
};