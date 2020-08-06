#include "City.h"

City::City(string name, long peoplesCount) : _name(std::move(name)), _peoplesCount(peoplesCount)
{
}

City::City() : _name("Unknown"), _peoplesCount(0)
{
}

bool City::operator ==(City& other)
{
	return _name == other._name && _peoplesCount == other._peoplesCount;
}

City& City::operator=(City other)
{
	if(this == &other)
		return *this;
	_name = other._name;
	_peoplesCount= other._peoplesCount;
	return *this;
}

ostream& operator<<(ostream& out, City& clone)
{
	return out << clone._name << ' ' << clone._peoplesCount;
}