#include "Agent.h"
#include "Running.h"
#include "Walking.h"


Agent::Agent() :
	_machine(std::make_shared<Machine>(std::make_shared<Walking>())),
	_up(false), _down(false), _left(false), _right(false)
{
	_machine->addState(std::make_shared<Running>());
}


Agent::~Agent()
{

}

void Agent::tick()
{
	handleInput();

	_machine->tick();
}

void Agent::reason()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		_machine->setState("Running");
	}
	else
	{
		_machine->setState("Walking");
	}

}

void Agent::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_up)
	{
		_up = true;
		std::cout << "Moving up: " << _machine->getCurrentState().getName() << std::endl;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_up = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !_down)
	{
		_down = true;
		std::cout << "Moving Down: " << _machine->getCurrentState().getName() << std::endl;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_down = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_left)
	{
		_left = true;
		std::cout << "Moving Left: " << _machine->getCurrentState().getName() << std::endl;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_left = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_right)
	{
		_right = true;
		std::cout << "Moving Right: " << _machine->getCurrentState().getName() << std::endl;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_right = false;
	}
}
