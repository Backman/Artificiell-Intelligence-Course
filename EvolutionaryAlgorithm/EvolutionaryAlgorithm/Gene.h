#pragma once

#include <cstdlib>
#include <assert.h>

class Gene
{
public:
	Gene()
	{
		randomize();
	}

	~Gene()
	{ }

	void randomize()
	{
		_char = (rand() % 90) + 32;
	}

	char getChar() 
	{ 
		return _char;
	}

	char getChar() const
	{
		return _char;
	}

	void setChar(char c) 
	{ 
		_char = c; 
	}

private:
	char _char;
};