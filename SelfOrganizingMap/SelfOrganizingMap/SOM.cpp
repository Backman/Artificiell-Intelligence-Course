#include "SOM.h"
#include "Utility.h"
#include "Constants.h"

SOM::SOM(int rows, int cols, int cellSize, int epochs) :
	_rows(rows), _cols(cols),
	_currentEpoch(0), _isDone(false)
{
	initSOM(rows, cols, cellSize);

	_timeConstant = epochs / std::log(START_RADIUS);
	_timeConstant *= 3.0f;
}


SOM::~SOM()
{
}

void SOM::draw(sf::RenderWindow* window)
{
	for (auto& cell : _nodes) {
		cell.renderNode(window);
	}
}

std::vector<float> SOM::getRandomSample()
{
	float r = Utility::randomFloatRange(0.0, 1.0f);
	float g = Utility::randomFloatRange(0.0, 1.0f);
	float b = Utility::randomFloatRange(0.0, 1.0f);

	std::vector<float> ret(3);
	ret[0] = r;
	ret[1] = g;
	ret[2] = b;

	return ret;
}

Node& SOM::getBMU(const std::vector<float>& input)
{
	Node* bmu = nullptr;
	float minVal = 999999999.0f;

	for (auto& node : _nodes) {
		float distance = node.getDistance(input);
		if (distance < minVal) {
			minVal = distance;
			bmu = &node;
		}
	}

	return *bmu;
}

void SOM::train(int epochCount, const std::vector<std::vector<float>>& targetSets)
{
	if (epochCount > 0) {
		int size = targetSets.size();
		int targetIndex = Utility::randomIntRange(0, size - 1);
		std::vector<float> target = targetSets[targetIndex];

		Node& bmu = getBMU(target);

		float radius = neighbourhoodRadius(_currentEpoch, _timeConstant);

		for (auto& node : _nodes) {
			float distSqr = Node::euclidianDistanceSqr(bmu, node);

			float radiusSqr = radius * radius;

			// If this node is inside the neighbourhood radius 
			if (distSqr < radiusSqr) {
				float learningRate = learningRateFunction(_currentEpoch, epochCount);
				float gaussian = exp(-distSqr / (2 * radiusSqr));

				node.adjustWeight(learningRate, gaussian, target);
			}
		}

		++_currentEpoch;
	}
	else {
		_isDone = true;
	}
}

bool SOM::isDone() const
{
	return _isDone;
}

int SOM::getEpochCount() const
{
	return _currentEpoch;
}

void SOM::initSOM(int rows, int cols, int cellSize)
{
	int xOffset = 0;
	int yOffset = 0;
	for (int y = 0; y < cols; ++y) {
		for (int x = 0; x < rows; ++x) {
			_nodes.push_back(Node(xOffset, yOffset, cellSize, cellSize, 3));
			xOffset += cellSize;
		}
		xOffset = 0;
		yOffset += cellSize;
	}
}

float SOM::neighbourhoodRadius(int t, float timeConstant)
{
	float e = exp(-(float)t / timeConstant);
	float a = START_RADIUS * e;

	return a;
}

float SOM::learningRateFunction(int t, float timeConstant)
{
	float e = exp(-(float)t / timeConstant);
	float a = START_LEARNING_RATE * e;

	return a;
}