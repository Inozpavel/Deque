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

	// ��������� ���� ����������� ������ Person �� ��������
	bool operator ==(City& other);

	// ��� ����������� ��������
	City& operator=(City other);

	// ��� ������ �� �������
	friend ostream& operator <<(ostream& out, City& clone);
};

#endif



