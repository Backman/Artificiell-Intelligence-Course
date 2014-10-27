#include <iostream>

#include <SFML\Graphics.hpp>
#include "Mouse.h"

int main()
{
	Mouse mouse;

	while (1)
	{
		mouse.tick();
	}

	/*sf::RenderWindow window(sf::VideoMode(1280, 720), "Stack FSM");

	while (window.isOpen())
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		mouse.tick();

		window.clear();

		mouse.render(&window);

		window.display();
	}*/

	return 0;
}