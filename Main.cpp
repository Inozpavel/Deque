#include <iostream>
#include <Windows.h>

#include "Deque.h"
#include "City.h"

using namespace std;

unsigned SelectOption(string name, vector<string> options);
bool EnterIndex(unsigned& index, const string& msg = "Введите позицию: ");
City Input(const string& msg = "Введите название города и количество жителей: ");
void AddElement();
void RemoveElement();
void FindElement();
void UpdateElement();
void SwapElements();
void PrintAll();

Deque<City> list;

/* 	
	Полная структура меню:
		1 Добавить элемент
			1 В начало
			2 В конец
			3 В произвольное место

		2 Удалить элемент
			1 Первый элемент
			2 Последний элемент
			3 По значению
				1 Первое вхождение
					1 С начала списка
					2 С конца списка
				2 Все вхождения
			4 С начальной позиции до конечной

		3 Найти элемент
			1 Первое вхождение
				1 С начала списка
				2 С конца списка
			2 Все вхождения

		4 Изменить элемент
			1 По значению
				1 Первое вхождение
					1 С начала списка
					2 С конца списка
				2 Все вхождения
			2 По позиции

		5 Поменять два элемента местами

		6 Вывести количество элементов в списке

		7 Вывести список на экран
			1 С начала
			2 С конца

		8 Очистить список
		9 Завершить программу
*/

int main()
{
	system("title Deque");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	system("cls");
	cout << endl;
	try
	{
		while (true)
		{
			switch (SelectOption("Список доступных действий:",
				{ "Добавить элемент",
					"Удалить элемент(ы)",
					"Найти элемент(ы)",
					"Изменить элемент(ы)",
					"Поменять два элемента местами",
					"Вывести количество элементов в списке",
					"Вывести список",
					"Очистить список",
					"Завершить программу"
				}))
			{
			case 0:
				system("cls");
				break;
			case 1:
				AddElement();
				break;
			case 2:
				RemoveElement();
				break;
			case 3:
				FindElement();
				break;
			case 4:
				UpdateElement();
				break;
			case 5:
				SwapElements();
				break;
			case 6:
				cout << "Размер списка : \t" << list.size() << endl;
				break;
			case 7:
				PrintAll();
				break;
			case 8:
				list.clear();
				break;
			case 9:
				throw exception("Программа завершила свою работу.");
			default:
				throw exception("Некорректный ввод! Программа завершила свою работу.");
				
			}
			cout << endl;
		}
	}
	catch(exception ex)
	{
		cout << endl << ex.what() << endl;
		system("pause");
	}	
	return 0;
}

unsigned SelectOption(string name, vector<string> options)
{
	cout << name << endl;
	for (int i = 0; i < options.size(); i++)
		cout << '\t' << i + 1 << ".\t" << options[i] << endl;
	cout << "Ваш выбор: ";
	unsigned choise;
	if (!(cin >> choise)) return Deque<int>::NOT_FOUND;
	return choise;
}

bool EnterIndex(unsigned& index, const string& msg)
{
	cout << msg;
	cin >> index;
	if (index >= list.size() || index < 0)
	{
		cout << "Некорретно указан индекс!\n";
		return false;
	}
	return true;
}

City Input(const string& msg)
{
	string name;
	unsigned numberOfPeople;

	cout << msg;
	cin >> name >> numberOfPeople;
	City city(name, numberOfPeople);
	return city;
}

void AddElement()
{
	switch (SelectOption("Выберите место:",
		{	"В начало",
			"В конец",
			"В произвольное место"
		})) 
	{
	case 1:
		list.push_front(Input());
		break;
	case 2:
		list.push_back(Input());
		break;
	case 3:
		unsigned index;
		EnterIndex(index);
		if (index > list.size())
		{
			cout << "Некорретно указан индекс!\n";
			break;
		}
		list.insert(index, Input());
		break;
	default:
		throw exception("Некорректный ввод! Программа завершила свою работу.");
	}
}

void RemoveElement()
{
	if (list.size() == 0)
	{
		cout << "Список пуст, действие невозможно." << endl;
		return;
	}

	City city;
	switch (SelectOption("Удалить элемент:",
		{	"Первый",
			"Последний",
			"По значению",
			"С начальной позиции до конечной позиций"
		})) 
	{
	case 1:
		if (!list.remove_at(0))
			cout << "Удалить не удалось! Список пуст!" << endl;
		break;
	case 2:
		if (!list.pop_back())
			cout << "Удалить не удалось! Список пуст!" << endl;
		break;
	case 3:
		switch (SelectOption("Количество удалений:",
			{	"Только первое найденное значение",
				"Только последнее найденное значение",
				"Все найденные значения" 
			}))
		{
		case 1:
			if (!list.remove(Input()))
				cout << "Значение не найдено, ничего не удалено.\n";
			break;
		case 2:
			if (!list.remove_last(Input()))
				cout << "Значение не найдено, ничего не удалено.\n";
			break;
		case 3:
			cout << "Удалено элементов: " << list.remove_all(Input()) << endl;
			break;
		}
		break;
	case 4 :
		unsigned startIndex, stopIndex;
		if (!EnterIndex(startIndex, "Введите начальную позицию: "))
			return;
		if (!EnterIndex(stopIndex, "Введите конечную позицию: "))
			return;
		list.erase(startIndex, stopIndex);
	default:
		throw exception("Некорректный ввод! Программа завершила свою работу.");
	}
}

void FindElement()
{
	if (list.size() == 0)
	{
		cout << "Список пуст, действие невозможно." << endl;
		return;
	}

	unsigned found;
	vector<unsigned> founds;

	switch (SelectOption("Найти:", 
		{	"Первый",
			"Все" 
		}))
	{
	case 1:
		switch (SelectOption("Найти:",
			{	"С начала списка",
				"С конца списка"
			}))
		{
		case 1:
			found = list.find(Input());
			break;
		case 2: 
			found = list.find_last(Input());
			break;
		default:
			throw exception("Некорректный ввод! Программа завершила свою работу.");
		}
		if (found == list.NOT_FOUND)
		{
			cout << "Элемент не найден.\n";
			break;
		}
		cout << "Элемент найден на позиции [" << found << "]\n";
		break;
	case 2:
		founds = list.find_all(Input());
		if (founds.empty())
		{
			cout << "Элемент не найден.\n";
			break;
		}
		cout << "Элемент найден на позици" << (founds.size() > 1 ? "ях:" : "и:");
		for (auto& element : founds)
			cout << " [" << element << "]";
		cout << endl;
		break;
	default:
		throw exception("Некорректный ввод! Программа завершила свою работу.");
	}
}

void UpdateElement()
{
	if (list.size() == 0)
	{
		cout << "Список пуст, действие невозможно." << endl;
		return;
	}

	City oldElement, newElement;
	switch (SelectOption("Изменить элемент по:", {
		"Значению",
		"Позиции"
		})) 
	{
	case 1:
		oldElement = Input("Введите старое значение: ");
		newElement = Input("Введите новое значение: ");
		switch (SelectOption("Способ замены:",
			{ "Заменить первый",
			  "Заменить последний",
			  "Заменить все" 
			}))
		{
		case 1:
			if (!list.update(oldElement, newElement))
				cout << "Элемент не найден, замены не произошло!" << endl;
			break;
		case 2:
			if (!list.update_last(oldElement, newElement))
				cout << "Элемент не найден, замены не произошло!" << endl;
			break;
		case 3:
			cout << "Количество замен: " << list.update_all(oldElement, newElement) << endl;
			break;
		default:
			throw exception("Некорректный ввод! Программа завершила свою работу.");
		}
		break;
	case 2:
		unsigned pos;
		if (EnterIndex(pos))
			list[pos] = Input();
		break;
	default:
		throw exception("Некорректный ввод! Программа завершила свою работу.");
	}
}

void SwapElements()
{
	if (list.size() == 0)
	{
		cout << "Список пуст, действие невозможно." << endl;
		return;
	}
	unsigned index1, index2;
	if (!EnterIndex(index1, "Введите первую позицию: "))
		return;
	if (!EnterIndex(index2, "Введите вторую позицию: "))
		return;
	list.swap(index1, index2);
}

void PrintAll()
{
	if (list.size() == 0)
	{
		cout << "Список пуст!" << endl;
		return;
	}
	switch (SelectOption("Вывести список:", {
		"С начала",
		"С конца"
		}))
	{
	case 1:
		list.print_all();
		break;
	case 2:
		list.print_all(true);
		break;
	default:
		throw exception("Некорректный ввод! Программа завершила свою работу.");
	}
}

