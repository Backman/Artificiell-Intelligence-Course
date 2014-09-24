
#include "PuzzleState.h"

int main()
{
	AStarSearcher<PuzzleState> aStar;

	PuzzleState startState;
	PuzzleState goalState;

	startState.tiles = g_start;
	goalState.tiles = g_goal;

	aStar.setStartAndGoal(startState, goalState);

	AStarSearcher<PuzzleState>::SearchState state = aStar.step();
	//aStar.getCurrentNode()->state.printState();

	while (state == AStarSearcher<PuzzleState>::SearchState::SEARCHING) {
		state = aStar.step();

	}

	std::vector<PuzzleState> solution;
	aStar.getSolution(solution);

	for (int i = solution.size() - 1; i >= 0; --i) {
		solution[i].printState();

	}

	std::cout << "Steps: " << aStar.getTotalSteps() << std::endl;
	std::cout << "Allocated count: " << aStar.getAllocatedCount() << std::endl;
	std::cout << "Number of steps: " << solution.size() << std::endl;

	std::cin.get();
	return EXIT_SUCCESS;
}