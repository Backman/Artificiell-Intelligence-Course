#include "DungeonGenerator.h"
#include "BSPDungeon.h"
#include "Level.h"

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1024, 760), "Dungeon Generator");

	Level l;
	l.init(500, 500, 10);

	DungeonGenerator generator(1024, 760);
	generator.generate(150, 5, 2, 10);

	BSPDungeon bsp;

	//bsp.generate(500, 500, 8);

	while (window.isOpen())
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed || evt.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}

			if (evt.key.code == sf::Keyboard::R)
			{
				generator.generate(30, 5, 3, 6);
			}
		}

		//generator.seperate();

		window.clear(sf::Color(0.2f * 255, 0.2f * 255, 0.2f * 255, 255));
		//l.render(&window);
		generator.render(&window);
		//bsp.render(&window);
		window.display();
	}


	return 0;
}
////
////#include <iostream>
////#include <string>
////#include <random>
////#include <cassert>
////#include <algorithm>
////
////enum class Tile
////{
////	Unused,
////	DirtWall,
////	DirtFloor,
////	Corridor,
////	Door,
////	UpStairs,
////	DownStairs
////};
////
////enum class Direction
////{
////	North, South, East, West,
////};
////
////class Map
////{
////public:
////
////	Map() :
////		xSize(0), ySize(0),
////		data() { }
////
////	Map(int x, int y, Tile value = Tile::Unused) :
////		xSize(x), ySize(y),
////		data(x * y, value) { }
////
////	void SetCell(int x, int y, Tile celltype)
////	{
////		assert(IsXInBounds(x));
////		assert(IsYInBounds(y));
////
////		data[x + xSize * y] = celltype;
////	}
////
////	Tile GetCell(int x, int y) const
////	{
////		assert(IsXInBounds(x));
////		assert(IsYInBounds(y));
////
////		return data[x + xSize * y];
////	}
////
////	void SetCells(int xStart, int yStart, int xEnd, int yEnd, Tile cellType)
////	{
////		assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
////		assert(IsYInBounds(yStart) && IsYInBounds(yEnd));
////
////		assert(xStart <= xEnd);
////		assert(yStart <= yEnd);
////
////		for (auto y = yStart; y != yEnd + 1; ++y)
////		for (auto x = xStart; x != xEnd + 1; ++x)
////			SetCell(x, y, cellType);
////	}
////
////	bool IsXInBounds(int x) const
////	{
////		return x >= 0 && x < xSize;
////	}
////
////	bool IsYInBounds(int y) const
////	{
////		return y >= 0 && y < ySize;
////	}
////
////	bool IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd)
////	{
////		assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
////		assert(IsYInBounds(yStart) && IsYInBounds(yEnd));
////
////		assert(xStart <= xEnd);
////		assert(yStart <= yEnd);
////
////		for (auto y = yStart; y != yEnd + 1; ++y)
////		for (auto x = xStart; x != xEnd + 1; ++x)
////		if (GetCell(x, y) != Tile::Unused)
////			return false;
////
////		return true;
////	}
////
////	bool IsAdjacent(int x, int y, Tile tile)
////	{
////		assert(IsXInBounds(x - 1) && IsXInBounds(x + 1));
////		assert(IsYInBounds(y - 1) && IsYInBounds(y + 1));
////
////		return
////			GetCell(x - 1, y) == tile || GetCell(x + 1, y) == tile ||
////			GetCell(x, y - 1) == tile || GetCell(x, y + 1) == tile;
////	}
////
////	void Print() const
////	{
////		// TODO: proper ostream iterator.
////		// TODO: proper lookup of character from enum.
////
////		for (auto y = 0; y != ySize; y++)
////		{
////			for (auto x = 0; x != xSize; x++)
////			{
////				switch (GetCell(x, y))
////				{
////				case Tile::Unused:
////					std::cout << " ";
////					break;
////				case Tile::DirtWall:
////					std::cout << "#";
////					break;
////				case Tile::DirtFloor:
////					std::cout << ".";
////					break;
////				case Tile::Corridor:
////					std::cout << ".";
////					break;
////				case Tile::Door:
////					std::cout << "+";
////					break;
////				case Tile::UpStairs:
////					std::cout << "<";
////					break;
////				case Tile::DownStairs:
////					std::cout << ">";
////					break;
////				};
////			}
////
////			std::cout << std::endl;
////		}
////
////		std::cout << std::endl;
////	}
////
////private:
////
////	int xSize, ySize;
////
////	std::vector<Tile> data;
////};
////
////class DungeonGenerator
////{
////public:
////
////	int Seed;
////
////	int XSize, YSize;
////
////	int MaxFeatures;
////
////	int ChanceRoom, ChanceCorridor;
////
////	DungeonGenerator() :
////		Seed(std::random_device()()),
////		XSize(80), YSize(25),
////		MaxFeatures(100),
////		ChanceRoom(75), ChanceCorridor(25) { }
////
////	Map Generate()
////	{
////		// TODO: proper input validation.
////		assert(MaxFeatures > 0 && MaxFeatures <= 100);
////		assert(XSize > 3 && XSize <= 80);
////		assert(YSize > 3 && YSize <= 25);
////
////		auto rng = RngT(Seed);
////		auto map = Map(XSize, YSize, Tile::Unused);
////
////		MakeDungeon(map, rng);
////
////		return map;
////	}
////
////private:
////
////	typedef std::mt19937 RngT;
////
////	int GetRandomInt(RngT& rng, int min, int max) const
////	{
////		return std::uniform_int_distribution<int>(min, max)(rng);
////	}
////
////	Direction GetRandomDirection(RngT& rng) const
////	{
////		return Direction(std::uniform_int_distribution<int>(0, 3)(rng));
////	}
////
////	bool MakeCorridor(Map& map, RngT& rng, int x, int y, int maxLength, Direction direction) const
////	{
////		assert(x >= 0 && x < XSize);
////		assert(y >= 0 && y < YSize);
////
////		assert(maxLength > 0 && maxLength <= std::max(XSize, YSize));
////
////		auto length = GetRandomInt(rng, 2, maxLength);
////
////		auto xStart = x;
////		auto yStart = y;
////
////		auto xEnd = x;
////		auto yEnd = y;
////
////		if (direction == Direction::North)
////			yStart = y - length;
////		else if (direction == Direction::East)
////			xEnd = x + length;
////		else if (direction == Direction::South)
////			yEnd = y + length;
////		else if (direction == Direction::West)
////			xStart = x - length;
////
////		if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
////			return false;
////
////		if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
////			return false;
////
////		map.SetCells(xStart, yStart, xEnd, yEnd, Tile::Corridor);
////
////		//std::cout << "Corridor: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;
////
////		return true;
////	}
////
////	bool MakeRoom(Map& map, RngT& rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction) const
////	{
////		// Minimum room size of 4x4 tiles (2x2 for walking on, the rest is walls)
////		auto xLength = GetRandomInt(rng, 4, xMaxLength);
////		auto yLength = GetRandomInt(rng, 4, yMaxLength);
////
////		auto xStart = x;
////		auto yStart = y;
////
////		auto xEnd = x;
////		auto yEnd = y;
////
////		if (direction == Direction::North)
////		{
////			yStart = y - yLength;
////			xStart = x - xLength / 2;
////			xEnd = x + (xLength + 1) / 2;
////		}
////		else if (direction == Direction::East)
////		{
////			yStart = y - yLength / 2;
////			yEnd = y + (yLength + 1) / 2;
////			xEnd = x + xLength;
////		}
////		else if (direction == Direction::South)
////		{
////			yEnd = y + yLength;
////			xStart = x - xLength / 2;
////			xEnd = x + (xLength + 1) / 2;
////		}
////		else if (direction == Direction::West)
////		{
////			yStart = y - yLength / 2;
////			yEnd = y + (yLength + 1) / 2;
////			xStart = x - xLength;
////		}
////
////		if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
////			return false;
////
////		if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
////			return false;
////
////		map.SetCells(xStart, yStart, xEnd, yEnd, Tile::DirtWall);
////		map.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, Tile::DirtFloor);
////
////		//std::cout << "Room: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;
////
////		return true;
////	}
////
////	bool MakeFeature(Map& map, RngT& rng, int x, int y, int xmod, int ymod, Direction direction) const
////	{
////		// Choose what to build
////		auto chance = GetRandomInt(rng, 0, 100);
////
////		if (chance <= ChanceRoom)
////		{
////			if (MakeRoom(map, rng, x + xmod, y + ymod, 8, 6, direction))
////			{
////				map.SetCell(x, y, Tile::Door);
////
////				// Remove wall next to the door.
////				map.SetCell(x + xmod, y + ymod, Tile::DirtFloor);
////
////				return true;
////			}
////
////			return false;
////		}
////		else
////		{
////			if (MakeCorridor(map, rng, x + xmod, y + ymod, 6, direction))
////			{
////				map.SetCell(x, y, Tile::Door);
////
////				return true;
////			}
////
////			return false;
////		}
////	}
////
////	bool MakeFeature(Map& map, RngT& rng) const
////	{
////		auto tries = 0;
////		auto maxTries = 1000;
////
////		for (; tries != maxTries; ++tries)
////		{
////			// Pick a random wall or corridor tile.
////			// Make sure it has no adjacent doors (looks weird to have doors next to each other).
////			// Find a direction from which it's reachable.
////			// Attempt to make a feature (room or corridor) starting at this point.
////
////			int x = GetRandomInt(rng, 1, XSize - 2);
////			int y = GetRandomInt(rng, 1, YSize - 2);
////
////			if (map.GetCell(x, y) != Tile::DirtWall && map.GetCell(x, y) != Tile::Corridor)
////				continue;
////
////			if (map.IsAdjacent(x, y, Tile::Door))
////				continue;
////
////			if (map.GetCell(x, y + 1) == Tile::DirtFloor || map.GetCell(x, y + 1) == Tile::Corridor)
////			{
////				if (MakeFeature(map, rng, x, y, 0, -1, Direction::North))
////					return true;
////			}
////			else if (map.GetCell(x - 1, y) == Tile::DirtFloor || map.GetCell(x - 1, y) == Tile::Corridor)
////			{
////				if (MakeFeature(map, rng, x, y, 1, 0, Direction::East))
////					return true;
////			}
////			else if (map.GetCell(x, y - 1) == Tile::DirtFloor || map.GetCell(x, y - 1) == Tile::Corridor)
////			{
////				if (MakeFeature(map, rng, x, y, 0, 1, Direction::South))
////					return true;
////			}
////			else if (map.GetCell(x + 1, y) == Tile::DirtFloor || map.GetCell(x + 1, y) == Tile::Corridor)
////			{
////				if (MakeFeature(map, rng, x, y, -1, 0, Direction::West))
////					return true;
////			}
////		}
////
////		return false;
////	}
////
////	bool MakeStairs(Map& map, RngT& rng, Tile tile) const
////	{
////		auto tries = 0;
////		auto maxTries = 10000;
////
////		for (; tries != maxTries; ++tries)
////		{
////			int x = GetRandomInt(rng, 1, XSize - 2);
////			int y = GetRandomInt(rng, 1, YSize - 2);
////
////			if (!map.IsAdjacent(x, y, Tile::DirtFloor) && !map.IsAdjacent(x, y, Tile::Corridor))
////				continue;
////
////			if (map.IsAdjacent(x, y, Tile::Door))
////				continue;
////
////			map.SetCell(x, y, tile);
////
////			return true;
////		}
////
////		return false;
////	}
////
////	bool MakeDungeon(Map& map, RngT& rng) const
////	{
////		// Make one room in the middle to start things off.
////		MakeRoom(map, rng, XSize / 2, YSize / 2, 8, 6, GetRandomDirection(rng));
////
////		for (auto features = 1; features != MaxFeatures; ++features)
////		{
////			if (!MakeFeature(map, rng))
////			{
////				std::cout << "Unable to place more features (placed " << features << ")." << std::endl;
////				break;
////			}
////		}
////
////		if (!MakeStairs(map, rng, Tile::UpStairs))
////			std::cout << "Unable to place up stairs." << std::endl;
////
////		if (!MakeStairs(map, rng, Tile::DownStairs))
////			std::cout << "Unable to place down stairs." << std::endl;
////
////		return true;
////	}
////
////};
////
////int main()
////{
////	DungeonGenerator generator;
////
////	auto map = generator.Generate();
////
////	map.Print();
////
////	std::cin.get();
////	return 0;
////}
//
//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <cstdio>
//#include <ctime>
//
//class Dungeon
//{
//	int xmax;
//	int ymax;
//
//	int xsize;
//	int ysize;
//
//	int objects;
//
//	int chanceRoom;
//	int chanceCorridor;
//
//	int* dungeon_map;
//
//	long oldseed;
//
//	enum
//	{
//		tileUnused = 0,
//		tileDirtWall,
//		tileDirtFloor,
//		tileStoneWall,
//		tileCorridor,
//		tileDoor,
//		tileUpStairs,
//		tileDownStairs,
//		tileChest
//	};
//
//	std::string msgXSize;
//	std::string msgYSize;
//	std::string msgMaxObjects;
//	std::string msgNumObjects;
//	std::string msgHelp;
//	std::string msgDetailedHelp;
//
//	void setCell(int x, int y, int celltype)
//	{
//		dungeon_map[x + xsize * y] = celltype;
//	}
//	int getCell(int x, int y)
//	{
//		return dungeon_map[x + xsize * y];
//	}
//
//	int getRand(int min, int max)
//	{
//		time_t seed;
//		seed = time(NULL) + oldseed;
//		oldseed = seed;
//
//		srand(seed);
//
//		int n = max - min + 1;
//		int i = rand() % n;
//
//		if (i < 0)
//			i = -i;
//
//		return min + i;
//	}
//
//	bool makeCorridor(int x, int y, int lenght, int direction)
//	{
//		int len = getRand(2, lenght);
//		int floor = tileCorridor;
//		int dir = 0;
//		if (direction > 0 && direction < 4) dir = direction;
//
//		int xtemp = 0;
//		int ytemp = 0;
//
//		switch (dir)
//		{
//		case 0:
//		{
//				  if (x < 0 || x > xsize) return false;
//				  else xtemp = x;
//
//				  for (ytemp = y; ytemp > (y - len); ytemp--)
//				  {
//					  if (ytemp < 0 || ytemp > ysize) return false;
//					  if (getCell(xtemp, ytemp) != tileUnused) return false;
//				  }
//
//				  for (ytemp = y; ytemp > (y - len); ytemp--)
//				  {
//					  setCell(xtemp, ytemp, floor);
//				  }
//				  break;
//
//		}
//		case 1:
//		{
//				  if (y < 0 || y > ysize) return false;
//				  else ytemp = y;
//
//				  for (xtemp = x; xtemp < (x + len); xtemp++)
//				  {
//					  if (xtemp < 0 || xtemp > xsize) return false;
//					  if (getCell(xtemp, ytemp) != tileUnused) return false;
//				  }
//
//				  for (xtemp = x; xtemp < (x + len); xtemp++)
//				  {
//					  setCell(xtemp, ytemp, floor);
//				  }
//				  break;
//		}
//		case 2:
//		{
//				  if (x < 0 || x > xsize) return false;
//				  else xtemp = x;
//
//				  for (ytemp = y; ytemp < (y + len); ytemp++)
//				  {
//					  if (ytemp < 0 || ytemp > ysize) return false;
//					  if (getCell(xtemp, ytemp) != tileUnused) return false;
//				  }
//				  for (ytemp = y; ytemp < (y + len); ytemp++){
//					  setCell(xtemp, ytemp, floor);
//				  }
//				  break;
//		}
//		case 3:
//		{
//				  if (ytemp < 0 || ytemp > ysize) return false;
//				  else ytemp = y;
//
//				  for (xtemp = x; xtemp >(x - len); xtemp--){
//					  if (xtemp < 0 || xtemp > xsize) return false;
//					  if (getCell(xtemp, ytemp) != tileUnused) return false;
//				  }
//
//				  for (xtemp = x; xtemp > (x - len); xtemp--){
//					  setCell(xtemp, ytemp, floor);
//				  }
//				  break;
//		}
//		}
//		//woot, we're still here! let's tell the other guys we're done!!
//		return true;
//	}
//	bool makeRoom(int x, int y, int xlength, int ylength, int direction){
//		//define the dimensions of the room, it should be at least 4x4 tiles (2x2 for walking on, the rest is walls)
//		int xlen = getRand(4, xlength);
//		int ylen = getRand(4, ylength);
//		//the tile type it's going to be filled with
//		int floor = tileDirtFloor; //jordgolv..
//		int wall = tileDirtWall; //jordv????gg
//		//choose the way it's pointing at
//		int dir = 0;
//		if (direction > 0 && direction < 4) dir = direction;
//
//		switch (dir){
//		case 0:
//			//north
//			//Check if there's enough space left for it
//			for (int ytemp = y; ytemp >(y - ylen); ytemp--){
//				if (ytemp < 0 || ytemp > ysize) return false;
//				for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++){
//					if (xtemp < 0 || xtemp > xsize) return false;
//					if (getCell(xtemp, ytemp) != tileUnused) return false; //no space left...
//				}
//			}
//
//			//we're still here, build
//			for (int ytemp = y; ytemp >(y - ylen); ytemp--){
//				for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++){
//					//start with the walls
//					if (xtemp == (x - xlen / 2)) setCell(xtemp, ytemp, wall);
//					else if (xtemp == (x + (xlen - 1) / 2)) setCell(xtemp, ytemp, wall);
//					else if (ytemp == y) setCell(xtemp, ytemp, wall);
//					else if (ytemp == (y - ylen + 1)) setCell(xtemp, ytemp, wall);
//					//and then fill with the floor
//					else setCell(xtemp, ytemp, floor);
//				}
//			}
//			break;
//		case 1:
//			//east
//			for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++){
//				if (ytemp < 0 || ytemp > ysize) return false;
//				for (int xtemp = x; xtemp < (x + xlen); xtemp++){
//					if (xtemp < 0 || xtemp > xsize) return false;
//					if (getCell(xtemp, ytemp) != tileUnused) return false;
//				}
//			}
//
//			for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++){
//				for (int xtemp = x; xtemp < (x + xlen); xtemp++){
//
//					if (xtemp == x) setCell(xtemp, ytemp, wall);
//					else if (xtemp == (x + xlen - 1)) setCell(xtemp, ytemp, wall);
//					else if (ytemp == (y - ylen / 2)) setCell(xtemp, ytemp, wall);
//					else if (ytemp == (y + (ylen - 1) / 2)) setCell(xtemp, ytemp, wall);
//
//					else setCell(xtemp, ytemp, floor);
//				}
//			}
//			break;
//		case 2:
//			//south
//			for (int ytemp = y; ytemp < (y + ylen); ytemp++){
//				if (ytemp < 0 || ytemp > ysize) return false;
//				for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++){
//					if (xtemp < 0 || xtemp > xsize) return false;
//					if (getCell(xtemp, ytemp) != tileUnused) return false;
//				}
//			}
//
//			for (int ytemp = y; ytemp < (y + ylen); ytemp++){
//				for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++){
//
//					if (xtemp == (x - xlen / 2)) setCell(xtemp, ytemp, wall);
//					else if (xtemp == (x + (xlen - 1) / 2)) setCell(xtemp, ytemp, wall);
//					else if (ytemp == y) setCell(xtemp, ytemp, wall);
//					else if (ytemp == (y + ylen - 1)) setCell(xtemp, ytemp, wall);
//
//					else setCell(xtemp, ytemp, floor);
//				}
//			}
//			break;
//		case 3:
//			//west
//			for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++){
//				if (ytemp < 0 || ytemp > ysize) return false;
//				for (int xtemp = x; xtemp >(x - xlen); xtemp--){
//					if (xtemp < 0 || xtemp > xsize) return false;
//					if (getCell(xtemp, ytemp) != tileUnused) return false;
//				}
//			}
//
//			for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++){
//				for (int xtemp = x; xtemp >(x - xlen); xtemp--){
//
//					if (xtemp == x) setCell(xtemp, ytemp, wall);
//					else if (xtemp == (x - xlen + 1)) setCell(xtemp, ytemp, wall);
//					else if (ytemp == (y - ylen / 2)) setCell(xtemp, ytemp, wall);
//					else if (ytemp == (y + (ylen - 1) / 2)) setCell(xtemp, ytemp, wall);
//
//					else setCell(xtemp, ytemp, floor);
//				}
//			}
//			break;
//		}
//
//		//yay, all done
//		return true;
//	}
//	void showDungeon(){
//		for (int y = 0; y < ysize; y++){
//			for (int x = 0; x < xsize; x++){
//				//System.out.print(getCell(x, y));
//				switch (getCell(x, y)){
//				case tileUnused:
//					printf(" ");
//					break;
//				case tileDirtWall:
//					printf("#");
//					break;
//				case tileDirtFloor:
//					printf(".");
//					break;
//				case tileStoneWall:
//					printf("X");
//					break;
//				case tileCorridor:
//					printf(".");
//					break;
//				case tileDoor:
//					printf("+");
//					break;
//				case tileUpStairs:
//					printf("<");
//					break;
//				case tileDownStairs:
//					printf(">");
//					break;
//				case tileChest:
//					printf("*");
//					break;
//				};
//			}
//			//if (xsize <= xmax) printf("\n");
//		}
//	}
//	bool createDungeon(int inx, int iny, int inobj){
//		if (inobj < 1) objects = 10;
//		else objects = inobj;
//
//		//justera kartans storlek, om den ????r st????rre eller mindre ????n "gr????nserna"
//		//adjust the size of the map, if it's smaller or bigger than the limits
//		if (inx < 3) xsize = 3;
//		else if (inx > xmax) xsize = xmax;
//		else xsize = inx;
//
//		if (iny < 3) ysize = 3;
//		else if (iny > ymax) ysize = ymax;
//		else ysize = iny;
//
//		//printf("%s %d\n", msgXSize.c_str(), xsize);
//		//printf("%s %d\n", msgYSize.c_str(),  + ysize);
//		//printf("%s %d\n", msgMaxObjects.c_str(), objects);
//
//		//redefine the map var, so it's adjusted to our new map size
//		dungeon_map = new int[xsize * ysize];
//
//		//start with making the "standard stuff" on the map
//		for (int y = 0; y < ysize; y++){
//			for (int x = 0; x < xsize; x++){
//				//ie, making the borders of unwalkable walls
//				if (y == 0) setCell(x, y, tileStoneWall);
//				else if (y == ysize - 1) setCell(x, y, tileStoneWall);
//				else if (x == 0) setCell(x, y, tileStoneWall);
//				else if (x == xsize - 1) setCell(x, y, tileStoneWall);
//
//				//and fill the rest with dirt
//				else setCell(x, y, tileUnused);
//			}
//		}
//
//		/*******************************************************************************
//		And now the code of the random-map-generation-algorithm begins!
//		*******************************************************************************/
//
//		//start with making a room in the middle, which we can start building upon
//		makeRoom(xsize / 2, ysize / 2, 8, 6, getRand(0, 3)); //getrand saken f????r att slumpa fram riktning p?? rummet
//
//		//keep count of the number of "objects" we've made
//		int currentFeatures = 1; //+1 for the first room we just made
//
//		//then we sart the main loop
//		for (int countingTries = 0; countingTries < 1000; countingTries++){
//			//check if we've reached our quota
//			if (currentFeatures == objects){
//				break;
//			}
//
//			//start with a random wall
//			int newx = 0;
//			int xmod = 0;
//			int newy = 0;
//			int ymod = 0;
//			int validTile = -1;
//			//1000 chances to find a suitable object (room or corridor)..
//			//(yea, i know it's kinda ugly with a for-loop... -_-')
//			for (int testing = 0; testing < 1000; testing++){
//				newx = getRand(1, xsize - 1);
//				newy = getRand(1, ysize - 1);
//				validTile = -1;
//				//System.out.println("tempx: " + newx + "\ttempy: " + newy);
//				if (getCell(newx, newy) == tileDirtWall || getCell(newx, newy) == tileCorridor){
//					//check if we can reach the place
//					if (getCell(newx, newy + 1) == tileDirtFloor || getCell(newx, newy + 1) == tileCorridor){
//						validTile = 0; //
//						xmod = 0;
//						ymod = -1;
//					}
//					else if (getCell(newx - 1, newy) == tileDirtFloor || getCell(newx - 1, newy) == tileCorridor){
//						validTile = 1; //
//						xmod = +1;
//						ymod = 0;
//					}
//					else if (getCell(newx, newy - 1) == tileDirtFloor || getCell(newx, newy - 1) == tileCorridor){
//						validTile = 2; //
//						xmod = 0;
//						ymod = +1;
//					}
//					else if (getCell(newx + 1, newy) == tileDirtFloor || getCell(newx + 1, newy) == tileCorridor){
//						validTile = 3; //
//						xmod = -1;
//						ymod = 0;
//					}
//
//					//check that we haven't got another door nearby, so we won't get alot of openings besides
//					//each other
//					if (validTile > -1){
//						if (getCell(newx, newy + 1) == tileDoor) //north
//							validTile = -1;
//						else if (getCell(newx - 1, newy) == tileDoor)//east
//							validTile = -1;
//						else if (getCell(newx, newy - 1) == tileDoor)//south
//							validTile = -1;
//						else if (getCell(newx + 1, newy) == tileDoor)//west
//							validTile = -1;
//					}
//
//					//if we can, jump out of the loop and continue with the rest
//					if (validTile > -1) break;
//				}
//			}
//			if (validTile > -1){
//				//choose what to build now at our newly found place, and at what direction
//				int feature = getRand(0, 100);
//				if (feature <= chanceRoom){ //a new room
//					if (makeRoom((newx + xmod), (newy + ymod), 8, 6, validTile)){
//						currentFeatures++; //add to our quota
//
//						//then we mark the wall opening with a door
//						setCell(newx, newy, tileDoor);
//
//						//clean up infront of the door so we can reach it
//						setCell((newx + xmod), (newy + ymod), tileDirtFloor);
//					}
//				}
//				else if (feature >= chanceRoom){ //new corridor
//					if (makeCorridor((newx + xmod), (newy + ymod), 6, validTile)){
//						//same thing here, add to the quota and a door
//						currentFeatures++;
//
//						setCell(newx, newy, tileDoor);
//					}
//				}
//			}
//		}
//
//
//		/*******************************************************************************
//		All done with the building, let's finish this one off
//		*******************************************************************************/
//
//		//sprinkle out the bonusstuff (stairs, chests etc.) over the map
//		int newx = 0;
//		int newy = 0;
//		int ways = 0; //from how many directions we can reach the random spot from
//		int state = 0; //the state the loop is in, start with the stairs
//		while (state != 10){
//			for (int testing = 0; testing < 1000; testing++){
//				newx = getRand(1, xsize - 1);
//				newy = getRand(1, ysize - 2); //cheap bugfix, pulls down newy to 0<y<24, from 0<y<25
//
//				//System.out.println("x: " + newx + "\ty: " + newy);
//				ways = 4; //the lower the better
//
//				//check if we can reach the spot
//				if (getCell(newx, newy + 1) == tileDirtFloor || getCell(newx, newy + 1) == tileCorridor){
//					//north
//					if (getCell(newx, newy + 1) != tileDoor)
//						ways--;
//				}
//				if (getCell(newx - 1, newy) == tileDirtFloor || getCell(newx - 1, newy) == tileCorridor){
//					//east
//					if (getCell(newx - 1, newy) != tileDoor)
//						ways--;
//				}
//				if (getCell(newx, newy - 1) == tileDirtFloor || getCell(newx, newy - 1) == tileCorridor){
//					//south
//					if (getCell(newx, newy - 1) != tileDoor)
//						ways--;
//				}
//				if (getCell(newx + 1, newy) == tileDirtFloor || getCell(newx + 1, newy) == tileCorridor){
//					//west
//					if (getCell(newx + 1, newy) != tileDoor)
//						ways--;
//				}
//
//				if (state == 0){
//					if (ways == 0){
//						//we're in state 0, let's place a "upstairs" thing
//						setCell(newx, newy, tileUpStairs);
//						state = 1;
//						break;
//					}
//				}
//				else if (state == 1){
//					if (ways == 0){
//						//state 1, place a "downstairs"
//						setCell(newx, newy, tileDownStairs);
//						state = 10;
//						break;
//					}
//				}
//			}
//		}
//
//
//		//all done with the map generation, tell the user about it and finish
//		//printf("%s %d\n",msgNumObjects.c_str(), currentFeatures);
//
//		return true;
//	}
//
//	void cmain()
//	{
//		int x = 80;
//		int y = 25;
//		int dungeon_objects = 100;
//		dungeon_map = new int[x * y];
//		for (;;)
//		{
//			if (createDungeon(x, y, dungeon_objects))
//				showDungeon();
//			std::cin.get();
//		}
//	}
//public:
//	Dungeon()
//	{
//		xmax = 80;
//		ymax = 25;
//
//		xsize = 0;
//		ysize = 0;
//
//		objects = 0;
//
//		chanceRoom = 75;
//		chanceCorridor = 25;
//
//		msgXSize = "X size of dungeon: \t";
//		msgYSize = "Y size of dungeon: \t";
//		msgMaxObjects = "max # of objects: \t";
//		msgNumObjects = "# of objects made: \t";
//		msgHelp = "";
//		msgDetailedHelp = "";
//
//		cmain();
//	}
//};
//
//int main()
//{
//	Dungeon d;
//
//	return EXIT_SUCCESS;
//}