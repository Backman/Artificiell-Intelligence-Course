
#include <SFML\Graphics.hpp>
#include "Canvas.h"

const int CELL_SIZE = 10;

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;


int main()
{
	srand(time(NULL));


	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Self-Organizing Maps");

	int cols = WINDOW_WIDTH / CELL_SIZE;
	int rows = WINDOW_HEIGHT / CELL_SIZE;


	Canvas c = Canvas(cols, rows, CELL_SIZE);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				sf::Event::KeyEvent key = event.key;
				if (key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}



		window.clear();
		c.drawCanvas(&window);
		window.display();
	}

	return 0;
}