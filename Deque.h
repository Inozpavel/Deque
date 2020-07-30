#ifndef DEQUE_H
#define DEQUE_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Deque
{
	/*
	Структура двусвязного списка
	nullptr <- head <--> node_1 <--> ... <--> node_n <--> tail -> nullptr
	head - первый node
	tail - последний node
	Linked List[0] = head
	Linked List[1] = head->next
	Linked List[N-1] = tail
	Linked List[N-2] = tail->previous
	*/
private:
	//Узел списка, содержит данные, указатель на следующий и предыдущий элемент
	struct Node
	{
		T data;
		Node* next;
		Node* previous;

		Node(T data, Node* previous = nullptr, Node* current = nullptr) :
			data(data), next(current), previous(previous)
		{
			if (previous != nullptr)
			previous->next = this;

			if (current != nullptr)
			current->previous = this;
		}
	};
	Node* _head;
	Node* _tail;
	unsigned _nodesCount;

	// Удаляет элемент, сохраняя целосность списка
	bool _remove_node(Node* node)
	{
		if (node == nullptr) 
			return false;
		if (node->previous != nullptr)// head
			node->previous->next = node->next;
		else 
			_head = node->next;

		if (node->next != nullptr)// tail
			node->next->previous = node->previous;
		else 
			_tail = node->previous;

		delete node;
		_nodesCount--;
		return true;
	}

	// Ищет первый Node, данные в котором равны value
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _search(T value, Node* element = nullptr);

	// Ищет последний Node, данные в котором равны value
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _search_last(T value, Node* element = nullptr);

	// Ищет элемент по индексу
	// В стучае успеха возвращает указатель на него, иначе nullptr
	Node* _get_element(unsigned index)
	{
		if (index < 0 || index > _nodesCount)
			return nullptr;
		Node* element;
		if (index <= _nodesCount / 2)
		{
			element = _head;
			for (int i = 0; i < index; i++)
				element = element->next;
		}
		else
		{
			element = _tail;
			for (int i = _nodesCount - 1; i > index; i--)
				element = element->previous;
		}
		return element;
	}

public:

	static unsigned const NOT_FOUND = ~0;

	Deque() : _nodesCount(0), _head(nullptr), _tail(nullptr)
	{
	}

	// Добавление элемента на указанную позицию
	void insert(unsigned pos, T element)
	{
		if (pos < 0 || pos > _nodesCount)
			throw out_of_range("Ошибка! Некорректно задан индекс!");

		if (_nodesCount == 0)
		{
			_head = new Node(element);
			_tail = _head;
		}
		else
		{
			if (pos == _nodesCount)
				_tail = new Node(element, _tail, nullptr);
			else if (pos == 0)
				_head = new Node(element, nullptr, _head);
			else
			{
				Node* current = _get_element(pos);
				new Node(element, current->previous, current);
			}
		}
		_nodesCount++;
	}

	// Добавление элемента в начало
	void push_front(T element)
	{
		insert(0, element);
	}

	// Добавление элемента в конец
	void push_back(T element)
	{
		insert(_nodesCount, element);
	}

	// Удаление элемента с начала
	bool pop_back()
	{
		remove_at(_nodesCount - 1);
	}

	// Удаление элемента с конца
	bool pop_front()
	{
		remove_at(0);
	}

	// Оператор [ ] позволяет по индексу получить ссылку на элемент списка
	T& operator[](unsigned index)
	{
		Node* element = _get_element(index);
		if (element == nullptr)
			throw out_of_range("Ошибка! Некорректно задан индекс!");
		return element->data;
	}

	// Обмен местами элементов first и second
	void swap(unsigned firstPos, unsigned secondPos);

	// Удаление одного (первого) элемента по значению value
	// Вернёт true в случае успеха (нашёл)
	bool remove(T value);

	// Удаление последнего элемента по значению value
	// Вернёт true в случае успеха (нашёл)
	bool remove_last(T value);

	// Удаление элемента на позиции pos
	bool remove_at(unsigned pos)
	{
		if (!_remove_node(_get_element(pos)))
			return false;
		return true;
	}

	// Удаление всех элементов со значением value
	// Вернёт количество удалённых элементов
	unsigned remove_all(T value);

	// Поиск одного элемента по значению
	// В случае успеха вернёт позицию первого элемента
	unsigned find(T value, unsigned startPos = 0);

	// Поиск последнего элемента по значению
	// В случае успеха вернёт позицию первого элемента
	unsigned find_last(T value, unsigned startPos);

	// Поиск всех элементов со значением value
	// Вернёт список позиций найденных элементов
	vector<unsigned> find_all(T value);

	// Изменяет значение первого найденного элемента old_value на new_value 
	bool update(T oldValue, T newValue);

	// Изменяет значение последнего найденного вхождения old_value на new_value
	// Вернёт true при успехе
	bool update_last(T oldValue, T newValue);

	// Изменяет значение всех найденных вхождения old_value на new_value
	// Вернёт количество замен
	unsigned update_all(T oldValue, T newValue);

	// Возвращает длину списка
	unsigned size()
	{
		return _nodesCount;
	}

	// Выводит список на экран, если передать true выведет список в обратном порядке
	void print_all(bool reverse = false)
	{
		cout << "Список:" << endl;
		if (reverse == false)
		{
			for (Node* current = _head; current != nullptr; current = current -> next)
				cout << current->data << endl;
		}
		else
		{
			for (Node* current = _tail; current != nullptr; current = current->previous)
				cout << current->data << endl;
		}
		if (_nodesCount != 0)
			cout << endl;
	}

	// Удаляет все элементы из [start; stop]
	void erase(unsigned start, unsigned stop)
	{
		if (start == stop) 
			return;
		if (stop > _nodesCount)
			throw out_of_range("Ошибка! Некорректно задан индекс!");
		int max = max(start, stop);
		unsigned min = min(start, stop);
		
		while (min < max)
		{
			remove_at(min);
			max--;
		}
			
	}

	// Удаляет все элементы начиная со start
	void erase(unsigned start)
	{
		erase(start, _nodesCount);
	}

	// Очищает весь список
	void clear()
	{
		erase(0);
	}

	// Очистка памяти, удаление списка
	~Deque()
	{
		clear();
	}
};

#endif
