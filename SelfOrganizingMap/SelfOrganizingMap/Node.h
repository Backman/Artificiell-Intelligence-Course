#pragma once

#include <vector>

class Node
{
private:
	typedef std::vector<float> Weights;

public:
	Node(int weightCount);
	~Node();

	void addWeight(float weight);
	float getWeight(int idx) const;

	float operator[](int idx) const;

	static float getDistance(Weights& weights, const Weights& inputWeights);

private:
	void initWeights(int count);
	

	float _x, _y;
	Weights _weights;
};

