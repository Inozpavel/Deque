#ifndef DEQUE_H
#define DEQUE_H

#include <vector>
#include <iostream>
#include <algorithm>


using std::endl;
using std::out_of_range;
using std::cout;
using std::cin;
using std::min;
using std::max;
using std::vector;

template <typename T>
class Deque
{
	/*
	Структура двусторонней очереди
	nullptr <- head <--> node_1 <--> ... <--> node_n <--> tail -> nullptr
	head - первый node (узел)
	tail - последний node (узел)
	Deque[0] = head
	Deque[1] = head->next
	Deque[N-1] = tail
	Deque[N-2] = tail->previous
	*/
private:
	//Узел списка, содержит данные (data) типа T, 
	//указатель на следующий (next) и предыдущий элемент (previous)
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
	// Если элемент удален успешно, вернет true, иначе false
	bool _remove_node(Node* node)
	{
		if (node == nullptr)
			return false;
		if (node->previous != nullptr) // head
			node->previous->next = node->next;
		else
			_head = node->next;

		if (node->next != nullptr) // tail
			node->next->previous = node->previous;
		else
			_tail = node->previous;

		delete node;
		_nodesCount--;
		return true;
	}

	// Ищет первый или последний элемент, данные в котором равны value
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _search(T value, bool isSearchFromEnd, Node* element = nullptr)
	{
		Node* current = element;
		if (element == nullptr)
			current = isSearchFromEnd? _tail : _head;
		while (current != nullptr)
		{
			if (current->data == value)
				return current;
			current = isSearchFromEnd ? current->previous : current->next;
		}
		return nullptr;
	}

	// Ищет элемент по индексу
	// В стучае успеха возвращает указатель на него, иначе nullptr
	Node* _get_element(unsigned index)
	{
		if (index < 0 || index >= _nodesCount)
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

	// Ищет первый или последний элемент по значению
	// В случае успеха вернёт позицию элемента, иначе константу NOT_FOUND
	unsigned _find(T value, bool isStartingFromEnd, unsigned startIndex)
	{
		for (Node* current = _get_element(startIndex);
			current != nullptr;
			current = isStartingFromEnd ? current->previous : current->next)
		{
			if (current->data == value)
				return startIndex;
			startIndex = isStartingFromEnd ? --startIndex : ++startIndex;
		}
		return NOT_FOUND; // unsigned_max
	}

public:
	// Константа, которая возвращается из функций, в которох не было результата
	static unsigned const NOT_FOUND = ~0;

	Deque() : _nodesCount(0), _head(nullptr), _tail(nullptr)
	{
	}

#pragma region Adding elements

	// Добавление элемента на указанную позицию
	void insert(unsigned index, T newElement)
	{
		if (index < 0 || index > _nodesCount)
			throw out_of_range("Ошибка! Некорректно задан индекс!");

		if (_nodesCount == 0)
		{
			_head = new Node(newElement);
			_tail = _head;
		}
		else
		{
			if (index == _nodesCount)
				_tail = new Node(newElement, _tail, nullptr);
			else if (index == 0)
				_head = new Node(newElement, nullptr, _head);
			else
			{
				Node* current = _get_element(index);
				new Node(newElement, current->previous, current);
			}
		}
		_nodesCount++;
	}

	// Добавление элемента в начало
	void push_front(T newElement)
	{
		insert(0, newElement);
	}

	// Добавление элемента в конец
	void push_back(T newElement)
	{
		insert(_nodesCount, newElement);
	}

#pragma endregion
	
#pragma region Methods remove

	// Удаление одного (первого) элемента по значению value
	// Вернёт true в случае успешного удаления, иначе false
	bool remove(T value)
	{
		return _remove_node(_search(value, false));
	}

	// Удаление одного (последнего) элемента по значению value
	// Вернёт true в случае успешного удаления, иначе false
	bool remove_last(T value)
	{
		return _remove_node(_search(value, true));
	}

	// Удаление одного элемента на позиции pos
	// Вернёт true в случае успешного удаления, иначе false
	bool remove_at(unsigned pos)
	{
		return _remove_node(_get_element(pos));
	}

	// Удаление всех элементов со значением value
	// Вернёт количество удалённых элементов
	unsigned remove_all(T value)
	{
		unsigned removedCount = 0;
		while (remove(value))
			removedCount++;
		return removedCount;
	}		

#pragma endregion

#pragma region Methods find

	// Поиск одного элемента по значению
	// В случае успеха вернёт позицию первого элемента, иначе константу NOT_FOUND
	// Поиск начинается с первого элемента и пройдет до конца списка
	unsigned find(T value)
	{
		return _find(value, false, 0);
	}  
	// Поиск одного элемента по значению
	// В случае успеха вернёт позицию первого элемента, иначе константу NOT_FOUND
	// Поиск начнется с позиции pos	и пройдет до конца списка
	unsigned find(T value, unsigned startIndex)
	{
		return _find(value, false, startIndex);
	}

	// Поиск последнего элемента по значению
	// В случае успеха вернёт позицию первого элемента, иначе константу NOT_FOUND
	// Поиск начинается с последнего элемента и пройдет до начала списка
	unsigned find_last(T value)
	{
		return _find(value, true, _nodesCount - 1);
	} 

	// Поиск последнего элемента по значению
	// В случае успеха вернёт позицию первого элемента, иначе константу NOT_FOUND
	// Поиск начнется с позиции pos	и пройдет до начала списка
	unsigned find_last(T value, unsigned startIndex)
	{
		return _find(value, true, startIndex);
	}

	// Поиск всех элементов со значением value
	// Вернёт список (vector<unsigned>) всех позиций найденных элементов
	vector<unsigned> find_all(T value)
	{
		vector<unsigned> founds = {};
		unsigned index = 0;
		do
		{
			index = find(value, index);
			if (index != NOT_FOUND)
				founds.push_back(index);
			else
				break;
			index++;
		} while (index < _nodesCount);
		return founds;
	}

#pragma endregion

#pragma region Methods update

	// Изменяет значение первого найденного элемента со значением oldValue на newValue 
	// Вернёт true при в случае успеха, иначе false
	bool update(T oldValue, T newValue)
	{
		Node* element = _search(oldValue, false);
		if (element == nullptr)
			return false;
		element->data = newValue;
		return true;
	}

	// Изменяет значение последнего найденного элемента со значением oldValue на newValue 
	// Вернёт true при в случае успеха, иначе false
	bool update_last(T oldValue, T newValue)
	{		
		Node* element = _search(oldValue, true);
		if (element == nullptr)
			return false;
		element->data = newValue;
		return true;
	}

	// Изменяет значение всех элементов со значением oldValue на newValue 
	// Вернёт количество замен
	// Если oldValue и newValue равны, вернет 0
	unsigned update_all(T oldValue, T newValue)
	{
		if (oldValue == newValue)
			return 0;
		unsigned updatedCount = 0;
		while (update(oldValue, newValue))
			updatedCount++;
		return updatedCount;
	}

#pragma endregion

#pragma region Useful methods


	// Возвращает количество элементов в списке
	unsigned size()
	{
		return _nodesCount;
	}

	// Выводит список на экран, если передать true выведет список в обратном порядке
	void print_all(bool isPrintReversed = false)
	{
		cout << "Список:" << endl;
		if (isPrintReversed == false)
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

	// Оператор [ ] позволяет по индексу получить ссылку на данные элемента списка
	T& operator[](unsigned index)
	{
		Node* element = _get_element(index);
		if (element == nullptr)
			throw out_of_range("Ошибка! Некорректно задан индекс!");
		return element->data;
	}

	// Обмен местами элементов двух элементов
	void swap(unsigned firstElementIndex, unsigned secondElementIndex)
	{
		T tempdata = (*this)[firstElementIndex];
		(*this)[firstElementIndex] = (*this)[secondElementIndex];
		(*this)[secondElementIndex] = tempdata;
	}
#pragma endregion

#pragma region Methods pop erase clear

	// Удаление первого элемента с начала
	// Если элемент удален успешно, вернет true, иначе false
	bool pop_back()
	{
		return remove_at(_nodesCount - 1);
	}

	// Удаление первого элемента с конца
	// Если элемент удален успешно, вернет true, иначе false
	bool pop_front()
	{
		return remove_at(0);
	}

	// Удаляет все элементы из диапазона [start..stop]
	// stopIndex индекс включается в диапазон
	void erase(unsigned startIndex, unsigned stopIndex)
	{
		if (stopIndex >= _nodesCount)
			throw out_of_range("Ошибка! Некорректно задан индекс!");
		int max = max(startIndex, stopIndex);
		unsigned min = min(startIndex, stopIndex);
		
		while (min <= max)
		{
			remove_at(min);
			max--;
		}
			
	}

	// Удаляет все элементы начиная со start
	void erase(unsigned startIndex)
	{
		erase(startIndex, _nodesCount - 1);
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

#pragma endregion

};

#endif
