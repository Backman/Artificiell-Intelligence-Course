#pragma once

#include <vector>

template<typename T>
class Grid
{
public:
	Grid(int rows, int cols) :
		_data(rows * cols),
		_rows(rows), _cols(cols)
	{ }

	int rowCount() const
	{
		return _cols;
	}

	int colCount() const
	{
		return _rows;
	}

	const T& get(int row, int col) const
	{
		return _data[row * _cols + col];
	}

	void set(int row, int col, const T& val)
	{
		_data[row * _cols + col] = val;
	}

	bool isEmpty() const
	{
		return _data.empty();
	}



private:
	typedef std::vector<T> Data;
	Data _data;

	int _rows, _cols;
};


class Tile;

typedef Grid<Tile*> TileGrid;