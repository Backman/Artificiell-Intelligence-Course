#pragma once

#include <vector>
#include <memory>
#include <algorithm>


template<class T>
class AStarSearcher
{
		typedef T State;
	public:
		enum class SearchState
		{
			SEARCHING,
			SUCCEEDED
		};

		class Node
		{
		public:
			float cost, heuristic, total;
			Node* parent;
			State state;

			Node() :
				cost(0), heuristic(0), total(0),
				parent(nullptr)
		{ }
	};
	typedef std::vector<Node*> NodePtrList;

	AStarSearcher()
	{ }

	void setStartAndGoal(State& start, State& goal)
	{
		_state = SearchState::SEARCHING;

		_start = createNodePtr();
		_goal = createNodePtr();
		
		_start->state = start;
		_goal->state = goal;

		std::cout << "Start state: " << std::endl;
		_start->state.printState();
		std::cout << "Goal state: " << std::endl;;
		_goal->state.printState();

		_start->cost = 0;
		_start->heuristic = start.getHeuristic(goal);
		_start->total = _start->cost + _start->heuristic;

		_openList.push_back(_start);
		
		sortList(_openList);
	}

	SearchState step()
	{
		if (_state == SearchState::SUCCEEDED) {
			return _state;
		}

		++_steps;

		_current = _openList.back();
		_openList.pop_back();

		if (_current->state == _goal->state) {
			_goal->parent = _current->parent;
			_goal->cost = _current->cost;


			_state = SearchState::SUCCEEDED;
			return _state;
		}

		_current->state.expand(this, _current->state);

		NodePtrList::iterator child;
		for (child = _expandList.begin(); child != _expandList.end(); ++child) {
			float newCost = _current->cost + _current->state.distanceTo((*child)->state);

			int openListIdx;
			int closedListIdx;

			bool isInOpenList = listContains(_openList, (*child), &openListIdx);
			bool isInClosedList = listContains(_closedList, (*child), &closedListIdx);

			if (isInOpenList) {
				if ((*child)->cost <= newCost) {
					deleteNode((*child));
					continue;
				}

				NodePtrList::iterator it = _openList.begin() + openListIdx;
				deleteNode((*it));
				_openList.erase(it);
			}
			if (isInClosedList) {
				if ((*child)->cost <= newCost) {
					deleteNode((*child));
					continue;
				}

				NodePtrList::iterator it = _closedList.begin() + closedListIdx;
				deleteNode((*it));
				_closedList.erase(it);
			}

			float heuristic = (*child)->state.getHeuristic(_goal->state);
			(*child)->parent = _current;
			(*child)->cost = newCost;
			(*child)->heuristic = heuristic;
			(*child)->total = newCost + heuristic;

			_openList.push_back((*child));
			sortList(_openList);
		}

		_closedList.push_back(_current);
		_expandList.clear();
	}

	void solve()
	{
		if (_start == nullptr || _goal == nullptr) {
			return;
		}

		while (!_openList.empty()) {
			step();
		}
	}

	float solutionCost() const
	{
		if (_goal != nullptr && _state == SearchState::SUCCEEDED) {
			return _goal->cost;
		}
	}

	int getTotalSteps() const
	{
		return _steps;
	}

	int getAllocatedCount() const
	{
		return _allocatedCount;
	}

	bool listContains(NodePtrList& list, Node* node, int* outIdx)
	{
		for (int i = 0; i < list.size(); ++i) {
			if (list[i]->state == node->state) {
				*outIdx = i;
				return true;
			}
		}

		return false;
	}

	void addToExpandList(State& state)
	{
		Node* node = createNodePtr();

		node->state = state;
		_expandList.push_back(node);
	}

	Node* getCurrentNode() {
		return _current;
	}

	void clearLists()
	{
		clearList(_openList);
		clearList(_closedList);

		_expandList.clear();
	}

	void clearNodes()
	{
		clearLists();

		deleteNode(_goal);
		deleteNode(_current);
	}

	void deleteNode(Node* node)
	{
		if (node) {
			--_allocatedCount;
			delete node;
			node = nullptr;
		}
	}

	void clearList(NodePtrList& list)
	{
		while (!list.empty()) {
			deleteNode(list.back());
			list.pop_back();
		}
	}

	Node* createNodePtr()
	{
		++_allocatedCount;
		return new Node;
	}

	void getSolution(std::vector<State>& solution)
	{
		if (_state == SearchState::SUCCEEDED) {
			if (_goal->parent != nullptr) {
				solution.push_back(_goal->state);
				Node* parent = _goal->parent;
				
				while (parent != nullptr) {
					solution.push_back(parent->state);
					parent = parent->parent;
				}
			}
		}
	}

private:
	int _allocatedCount;
	struct NodeComparer
	{
		bool operator()(const Node& a, const Node& b) const
		{
			return a.total > b.total;
		}
		bool operator()(const Node* a, const Node* b) const
		{
			return a->total > b->total;
		}
	} comparer;

	void sortList(NodePtrList& list)
	{
		std::sort(list.begin(), list.end(), comparer);
	}

	Node* _start;
	Node* _goal;
	Node* _current;

	int _steps;
	
	NodePtrList _openList;
	NodePtrList _closedList;
	NodePtrList _expandList;
	std::vector<State> _solutionList;

	SearchState _state;
};