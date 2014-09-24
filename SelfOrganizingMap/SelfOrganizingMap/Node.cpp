#include "Node.h"
#include "Utility.h"


Node::Node(int left, int top, int width, int height, int weightCount)
{
	initWeights(weightCount);

	_x = left + (width / 2);
	_y = top + (height / 2);

	_rectShape.setSize(sf::Vector2f((float)width, (float)height));
	_rectShape.setOutlineColor(sf::Color::Black);
	_rectShape.setOutlineThickness(1.0f);
	_rectShape.setPosition(sf::Vector2f(left, top));
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

void Node::renderNode(sf::RenderWindow* window)
{
	int r = (int)(_weights[0] * 255);
	int g = (int)(_weights[1] * 255);
	int b = (int)(_weights[2] * 255);

	_rectShape.setFillColor(sf::Color(r, g, b));

	window->draw(_rectShape);
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

