#include <iostream>
#include <string>

#include "Machine.h"
#include "Agent.h"

#include "SFML\Graphics.hpp"

void handleKeyEvent(sf::Event::KeyEvent keyEvt, sf::Window& window);

int main()
{
	Agent agent;

	sf::Window window(sf::VideoMode(200, 200), "Finite State Machine");

	while (window.isOpen())
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			handleKeyEvent(evt.key, window);


			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		agent.reason();
		agent.tick();
	}

	return 0;
}

void handleKeyEvent(sf::Event::KeyEvent keyEvt, sf::Window& window)
{
	switch (keyEvt.code)
	{
	case sf::Keyboard::Escape:
		window.close();
		break;
	}
}