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


	static float getDistance(Weights& weights, const Weights& inputWeights);
private:
	void initWeights(int count);
	
	sf::RectangleShape _rectShape;
	float _x, _y;
	Weights _weights;
};

