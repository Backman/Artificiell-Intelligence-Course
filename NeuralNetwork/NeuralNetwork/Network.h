#pragma once

#include <vector>

typedef std::vector<float> Connections;

class Network
{
public:
	Network();
	~Network();

	void feedForward(const Connections& inputs);
	void backPropagation(const Connections& targets);
	void getResults(const Connections& results) const;

private:

	Connections _connections;
};

