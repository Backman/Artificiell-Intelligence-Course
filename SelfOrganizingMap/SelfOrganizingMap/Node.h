#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class Node
{
private:
	typedef std::vector<float> Weights;

public:
	Node(int left, int top, int width, int height, int weightCount);
	~Node();

	void addWeight(float weight);
	float getWeight(int idx) const;

	float operator[](int idx) const;

	void renderNode(sf::RenderWindow* window);

	void adjustWeight(float learningRate, float h, const std::vector<float>& target);

	float getX() const { return _x; }
	float getY() const { return _y; }

	float getDistance(const Weights& inputWeights);

	static float euclidianDistanceSqr(Node& a, Node& b);
private:
	void initWeights(int count);
	
	sf::RectangleShape _rectShape;
	float _x, _y;
	Weights _weights;
};

