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
	unsigned _peoplesCount;
public:

	City(string name, long peoplesCount);

	City();

	// —равнение двух экземпл€ров класса Person на равность
	bool operator ==(City& other);

	// ƒл€ копировани€ объектов
	City& operator=(City other);

	// ƒл€ вывода на консоль
	friend ostream& operator <<(ostream& out, City& clone);
};

#endif



