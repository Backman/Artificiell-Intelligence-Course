
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include "SOM.h"
#include "Manager.h"
#include "Constants.h"

int main()
{
	srand(time(NULL));


	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Self-Organizing Maps");

	int cols = WINDOW_WIDTH / CELL_SIZE;
	int rows = WINDOW_HEIGHT / CELL_SIZE;

	Manager manager(cols, rows, CELL_SIZE, NUM_EPOCHS);
	
	sf::Font font;
	font.loadFromFile("calibri.ttf");


	sf::Text text("", font);
	text.setPosition(sf::Vector2f(0.0f, 0.0f));

	bool train = false;
	int count = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				sf::Event::KeyEvent key = event.key;
				switch (key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;

				case sf::Keyboard::Space:
					//train = true;
					break;
				}
				if (key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (!manager.isDone())
		{
			manager.train();

			std::stringstream ss;
			ss << "Epoch: " << manager.getEpochCount();
			text.setString(ss.str());
		}

		window.clear();
		manager.draw(&window);
		window.draw(text);
		window.display();
	}

	return 0;
}