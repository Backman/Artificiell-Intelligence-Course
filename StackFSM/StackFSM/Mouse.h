#pragma once

#include <SFML\Graphics.hpp>
#include "StackFSM.h"


class Mouse
{
public:
	Mouse();
	~Mouse();
	int count = 0;

	void tick();
	void render(sf::RenderWindow* rw);

	void flee();
	void goHome();
	void findCheese();


private:
	bool increment;
	bool closeToRat;
	bool hasCheese;
	bool isHome;

	sf::Vector2f _pos;
	sf::RenderWindow* _window;

	StackFSM _machine;

	State findCheeseState, fleeState, goHomeState;
};

