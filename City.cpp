#include "City.h"

City::City(string name, long peoplesCount) : _name(std::move(name)), _numbersOfPeople(peoplesCount)
{
}

City::City() : _name("Unknown"), _numbersOfPeople(0)
{
}

bool City::operator ==(City& other)
{
	return _name == other._name && _numbersOfPeople == other._numbersOfPeople;
}

City& City::operator=(City other)
{
	if(this == &other)
		return *this;
	_name = other._name;
	_numbersOfPeople= other._numbersOfPeople;
	return *this;
}

ostream& operator<<(ostream& out, City& clone)
{
	return out << clone._name << ' ' << clone._numbersOfPeople;
}