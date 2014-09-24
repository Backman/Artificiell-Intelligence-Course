#pragma once

#include <stdio.h>
#include <iostream>
#include <array>
#include "AStarSearcher.h"

#define HEURISTIC_FUNC 0
const int WIDTH = 3;
const int HEIGHT = 3;

class PuzzleState
{
public:

	enum TILE_STATE
	{
		BLANK,
		TILE,
		NOT_ON_BOARD
	};

	std::array<int, WIDTH * HEIGHT> tiles;

	PuzzleState() 
	{

	}

	inline float getHeuristic(PuzzleState& goalState);
	inline bool operator==(const PuzzleState& rhs) const;
	inline void expand(AStarSearcher<PuzzleState>* searcer, PuzzleState& parentState);
	inline float distanceTo(PuzzleState& childState);
	inline void printState();

private:
	inline float manhattanDistance(PuzzleState& goalState);
	inline float nilssonSequence(PuzzleState& goalState);
	inline float s(PuzzleState& goalState);

	inline bool canMove(PuzzleState& toState, int blankX, int blankY, int targetX, int targetY);
	inline TILE_STATE getTile(int xPos, int yPos);
	inline void getBlankPosition(int* x, int* y);
	inline int getBlankPositionIdx();
};

std::array<int, WIDTH * HEIGHT> g_goal =
{
#if HEURISTIC_FUNC == 0
	1, 2, 3,
	4, 5, 6,
	7, 8, 0
#elif HEURISTIC_FUNC == 1
	1, 2, 3,
	8, 0, 4,
	7, 6, 5
#endif
};

std::array<int, WIDTH * HEIGHT> g_start =
{
#if HEURISTIC_FUNC == 0
	7, 2, 4,
	5, 0, 6,
	8, 3, 1
#elif HEURISTIC_FUNC == 1
	2, 1, 6,
	4, 0, 8,
	7, 5, 3
#endif
};

/**
	h3 : Sum of Manhattan distances of the tiles from their
	goal positions
	In the given figure, all the tiles are out of position, hence for this state,
	h3 = 3 + 1 + 2 + 2 + 2 + 3 + 3 + 2 = 18.
	h3 is an admissible heuristic, since in every move, one tile can only
	move closer to its goal by one step.
*/

/**
	Nilsson’s Sequence Score
	h(n) = P(n) + 3 S(n)
	P(n) : Sum of Manhattan distances of each tile from its proper position
	S(n) : A sequence score obtained by checking around the non-central 
	squares in turn, allotting 2 for every tile not followed by its proper 
	successor and 0 for every other tile, except that a piece in the center 
	scores 1
*/

inline PuzzleState::TILE_STATE PuzzleState::getTile(int xPos, int yPos)
{
	if (xPos < 0 || xPos >= WIDTH || yPos < 0 || yPos >= HEIGHT) {
		return PuzzleState::NOT_ON_BOARD;
	}

	if (tiles[(yPos * WIDTH) + xPos] == 0) {
		return PuzzleState::BLANK;
	}

	return PuzzleState::TILE;
}

inline bool PuzzleState::canMove(PuzzleState& toState, int blankX, int blankY, int targetX, int targetY)
{
	if (getTile(blankX, blankY) == PuzzleState::BLANK) {
		if (toState.getTile(targetX, targetY) == PuzzleState::TILE) {

			toState.tiles = tiles;
			
			toState.tiles[(targetY * WIDTH) + targetX] = tiles[(blankY * WIDTH) + blankX];
			toState.tiles[(blankY * WIDTH) + blankX] = tiles[(targetY * WIDTH) + targetX];

			return true;
		}
	}

	return false;
}

inline void PuzzleState::getBlankPosition(int* outX, int* outY)
{
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (tiles[(y * WIDTH) + x] == 0) {
				*outX = x;
				*outY = y;

				return;
			}
		}
	}
}

inline int PuzzleState::getBlankPositionIdx()
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i) {
		if (tiles[i] == 0) {
			return i;
		}
	}

	return -1;
}

inline float PuzzleState::getHeuristic(PuzzleState& goalState)
{
#if HEURISTIC_FUNC == 0
	return manhattanDistance(goalState);
#elif HEURISTIC_FUNC == 1
	return nilssonSequence(goalState);
#endif
}

inline float PuzzleState::manhattanDistance(PuzzleState& goalState)
{
	int posX, posY, goalX, goalY;
	int h = 0;

	for (int i = 0; i < WIDTH * HEIGHT; ++i) {
		if (tiles[i] == 0) {
			continue;
		}

		for (int j = 0; j < WIDTH * HEIGHT; ++j) {
			if (tiles[i] == goalState.tiles[j]) {
				goalX = j % WIDTH;
				goalY = j / WIDTH;
				break;
			}
		}

		posX = i % WIDTH;
		posY = i / HEIGHT;

		h += abs(goalX - posX);
		h += abs(goalY - posY);
	}

	return h;
}

inline float PuzzleState::nilssonSequence(PuzzleState& goalState)
{
	return manhattanDistance(goalState) + 3 * s(goalState);
}

inline float PuzzleState::s(PuzzleState& goalState)
{
	int s = 0.0f;

	return s;
}

inline bool PuzzleState::operator==(const PuzzleState& rhs) const
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i) {
		if (tiles[i] != rhs.tiles[i]) {
			return false;
		}
	}

	return true;
}

inline void PuzzleState::expand(AStarSearcher<PuzzleState>* searcer, PuzzleState& parentState)
{
	PuzzleState upState;
	PuzzleState downState;
	PuzzleState leftState;
	PuzzleState rightState;

	int blankX, blankY;
	getBlankPosition(&blankX, &blankY);

	if (canMove(upState, blankX, blankY, blankX, blankY - 1)) {
		searcer->addToExpandList(upState);
	}

	if (canMove(downState, blankX, blankY, blankX, blankY + 1)) {
		searcer->addToExpandList(downState);
	}

	if (canMove(leftState, blankX, blankY, blankX - 1, blankY)) {
		searcer->addToExpandList(leftState);
	}

	if (canMove(rightState, blankX, blankY, blankX + 1, blankY)) {
		searcer->addToExpandList(rightState);
	}

}

inline float PuzzleState::distanceTo(PuzzleState& childState)
{
	return 1.0f;
}

inline void PuzzleState::printState()
{
	char str[100];
	sprintf_s(str, "%c %c %c\n%c %c %c\n%c %c %c\n",
		tiles[0] + '0',
		tiles[1] + '0',
		tiles[2] + '0',
		tiles[3] + '0',
		tiles[4] + '0',
		tiles[5] + '0',
		tiles[6] + '0',
		tiles[7] + '0',
		tiles[8] + '0'
		);

	std::cout << str << std::endl;
}