#include "Entity.h"


Entity::Entity() : 
	findCheeseState(std::string("findCheese"), std::bind(&Entity::findCheese, this)),
	goHomeState(std::string("goHome"), std::bind(&Entity::goHome, this)),
	fleeState(std::string("flee"), std::bind(&Entity::flee, this)),
	closeToRat(false),
	hasCheese(false),
	isHome(false)
{
	_machine.pushState(findCheeseState);
}


Entity::~Entity()
{
}
