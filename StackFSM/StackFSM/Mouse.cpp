#include "Mouse.h"


Mouse::Mouse() :
	findCheeseState(std::string("findCheese"), std::bind(&Mouse::findCheese, this)),
	goHomeState(std::string("goHome"), std::bind(&Mouse::goHome, this)),
	fleeState(std::string("flee"), std::bind(&Mouse::flee, this)),
	closeToRat(false),
	hasCheese(false),
	isHome(false)
{
	_machine.pushState(findCheeseState);
}


Mouse::~Mouse()
{
}

void Mouse::tick()
{
	_machine.tick();

	isHome = false;
	hasCheese = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		closeToRat = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		closeToRat = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		hasCheese = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		isHome = true;
	}
}

void Mouse::render(sf::RenderWindow* rw)
{
	if (_window == nullptr)
	{
		_window = rw;
	}

	sf::RectangleShape s(sf::Vector2f(50, 50));
	s.setPosition(_pos);

	rw->draw(s);
}
static bool once = false;
void Mouse::flee()
{
	if (!once)
	{
		std::cout << "Fleeing from cat..." << std::endl;
		once = true;
	}
	if (!closeToRat)
	{
		once = false;
		_machine.popState();
	}
}

void Mouse::goHome()
{
	if (!once)
	{
		std::cout << "Going home..." << std::endl;
		once = true;
	}
	if (isHome)
	{
		once = false;
		_machine.popState();
		_machine.pushState(findCheeseState);
	}

	if (closeToRat)
	{
		once = false;
		_machine.pushState(fleeState);
	}
}

void Mouse::findCheese()
{
	if (!once)
	{
		std::cout << "Looking for cheese..." << std::endl;
		once = true;
	}
	if (hasCheese)
	{
		once = false;
		_machine.popState();
		_machine.pushState(goHomeState);
	}

	if (closeToRat)
	{
		once = false;
		_machine.pushState(fleeState);
	}
}