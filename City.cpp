#include "City.h"

City::City(string name, unsigned peoplesCount) : _name(std::move(name)), _numberOfPeople(peoplesCount)
{
}

City::City() : _name("Unknown"), _numberOfPeople(0)
{
}

bool City::operator ==(City& other)
{
	return _name == other._name && _numberOfPeople == other._numberOfPeople;
}

City& City::operator=(City other)
{
	if(this == &other)
		return *this;
	_name = other._name;
	_numberOfPeople= other._numberOfPeople;
	return *this;
}

ostream& operator<<(ostream& out, City& element)
{
	return out << element._name << ' ' << element._numberOfPeople;
}