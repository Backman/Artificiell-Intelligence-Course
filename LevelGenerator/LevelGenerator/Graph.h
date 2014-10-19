#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <set>
#include <map>

#include <iostream>

struct Vertex
{
	int id;
	sf::Vector2f* pos;
};

class Graph
{
public:
	Graph();
	Graph(int vertexCount);
	~Graph();

	void init(int vertexCount);

	void addEdge(int i, int j);
	void removeEdge(int i, int j);
	bool isEdge(int i, int j) const;

	int getEdge(int i, int j) const;

	int getVertexCount() const;

	void printGraph()
	{
		std::cout << "\t";
		for (int i = 0; i < _vertexCount; ++i)
		{
			std::cout << i << " ";
		}

		std::cout << std::endl;

		for (int i = 0; i < _vertexCount; ++i)
		{
			std::cout << i << ": \t";
			for (int j = 0; j < _vertexCount; ++j)
			{
				std::cout << _adjMatrix[i][j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

private:
	void initAdjMatrix(int vertexCount);
	int _vertexCount;

	int** _adjMatrix;
};