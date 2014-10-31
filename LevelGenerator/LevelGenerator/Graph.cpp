#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(int vertexCount) :
	_vertexCount(vertexCount)
{
	initAdjMatrix(vertexCount);
}

Graph::~Graph()
{
	clearGraph();
}

void Graph::clearGraph()
{
	for (int i = 0; i < _vertexCount; ++i)
	{
		if (_adjMatrix[i] != nullptr)
		{
			delete[] _adjMatrix[i];
			_adjMatrix[i] = nullptr;
		}
	}

	if (_adjMatrix != nullptr)
	{
		delete[] _adjMatrix;
		_adjMatrix = nullptr;
	}
	_vertexCount = 0;
}

void Graph::init(int vertexCount)
{
	initAdjMatrix(vertexCount);
	_vertexCount = vertexCount;
}

void Graph::initAdjMatrix(int vertexCount)
{
	_adjMatrix = new int*[vertexCount];
	for (int i = 0; i < vertexCount; ++i)
	{
		_adjMatrix[i] = new int[vertexCount];
		for (int j = 0; j < vertexCount; ++j)
		{
			_adjMatrix[i][j] = 0;
		}
	}
}

void Graph::addEdge(int i, int j)
{
	if (i >= 0 && i < _vertexCount && j > 0 && j < _vertexCount)
	{
		_adjMatrix[i][j] = 1;
		_adjMatrix[j][i] = 1;
	}
}

void Graph::removeEdge(int i, int j)
{
	if (i >= 0 && i < _vertexCount && j > 0 && j < _vertexCount)
	{
		_adjMatrix[i][j] = 0;
		_adjMatrix[j][i] = 0;
	}
}

bool Graph::isEdge(int i, int j) const
{
	return getEdge(i, j);
}

int Graph::getEdge(int i, int j) const
{
	if (i >= 0 && i < _vertexCount && j >= 0 && j < _vertexCount)
	{
		return _adjMatrix[i][j];
	}

	return 0;
}

int Graph::getVertexCount() const
{
	return _vertexCount;
}
