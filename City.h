#ifndef CITY_H
#define CITY_H

#include <string>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;

class City
{
private:

	string _name;
	unsigned _numberOfPeople;

public:

	City(string name, unsigned peoplesCount);

	City();

	// Сравнение двух экземпляров класса Person на равность
	bool operator ==(City& other);

	// Для копирования объектов
	City& operator=(City other);

	// Для вывода на консоль
	friend ostream& operator <<(ostream& out, City& element);
};

#endif
