#include "Node.h"
#include "Utility.h"

Node::Node(int weightCount)
{
	initWeights(weightCount);
}


Node::~Node()
{
}



void Node::addWeight(float weight)
{
	_weights.push_back(weight);
}

float Node::getWeight(int idx) const
{
	return _weights[idx];
}

float Node::operator[](int idx) const
{
	return _weights[idx];
}

/********************************
	Static functions
*********************************/

float Node::getDistance(Weights& weights, const Weights& inputWeights)
{
	float totalDist = 0;
	for (int i = 0; i < weights.size(); ++i) {
		float delta = inputWeights[i] - weights[i];
		totalDist += delta * delta;
	}

	return totalDist;
}

/********************************
	Private functions
*********************************/

void Node::initWeights(int count)
{
	for (int i = 0; i < count; ++i) {
		_weights.push_back(randomFloatRange());
	}
}

