#pragma once
class LevelGenerator
{
public:
	LevelGenerator();
	virtual ~LevelGenerator();

	virtual void generate() = 0;

protected:
};

