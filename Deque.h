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
	// Если элемент удален успешно, вернет true, иначе false
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

	// Ищет первый или последний Node, данные в котором равны value
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

	// Поиск первого или последнего элемента по значению
	// В случае успеха вернёт позицию первого элемента
	// По умолчанию поиск начинается с самого последнего элемента
	unsigned _find(T value, bool isFromEnd, unsigned startPos)
	{
		for (Node* current = _get_element(startPos);
			current != nullptr;
			current = isFromEnd ? current->previous : current->next)
		{
			if (current->data == value)
				return startPos;
			startPos = isFromEnd ? --startPos : ++startPos;
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


#pragma endregion

	// Оператор [ ] позволяет по индексу получить ссылку на элемент списка
	T& operator[](unsigned index)
	{
		Node* element = _get_element(index);
		if (element == nullptr)
			throw out_of_range("Ошибка! Некорректно задан индекс!");
		return element->data;
	}

	// Обмен местами элементов first и second
	void swap(unsigned firstPos, unsigned secondPos)
	{
		T tempdata = (*this)[firstPos];
		(*this)[firstPos] = (*this)[secondPos];
		(*this)[secondPos] = tempdata;
	}

#pragma region Methods remove

	// Удаление одного (первого) элемента по значению value
	// Вернёт true в случае успеха (нашёл)
	bool remove(T value)
	{
		return _remove_node(_search(value, false));
	}

	// Удаление последнего элемента по значению value
	// Вернёт true в случае успеха (нашёл)
	bool remove_last(T value)
	{
		return _remove_node(_search(value, true));
	}

	// Удаление элемента на позиции pos
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
	// В случае успеха вернёт позицию первого элемента
	// Поиск начинается с элемента под индексом 0
	unsigned find(T value)
	{
		return _find(value, false, 0);
	}  
	// Поиск одного элемента по значению
	// В случае успеха вернёт позицию первого элемента
	// Поиск начнется с позиции pos
	unsigned find(T value, unsigned startPos)
	{
		return _find(value, false, startPos);
	}

	// Поиск последнего элемента по значению
	// В случае успеха вернёт позицию первого элемента
	// Поиск начинается с самого последнего элемента
	unsigned find_last(T value)
	{
		return _find(value, true, _nodesCount - 1);
	} 

	// Поиск последнего элемента по значению
	// В случае успеха вернёт позицию первого элемента
	// Поиск начнется с позиции pos
	unsigned find_last(T value, unsigned startPos)
	{
		return _find(value, true, startPos);
	}

	// Поиск всех элементов со значением value
	// Вернёт список позиций найденных элементов
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

	// Изменяет значение первого найденного элемента old_value на new_value 
	bool update(T oldValue, T newValue)
	{
		Node* element = _search(oldValue, false);
		if (element == nullptr)
			return false;
		element->data = newValue;
		return true;
	}

	// Изменяет значение последнего найденного вхождения old_value на new_value
	// Вернёт true при успехе
	bool update_last(T oldValue, T newValue)
	{		
		Node* element = _search(oldValue, true);
		if (element == nullptr)
			return false;
		element->data = newValue;
		return true;
	}

	// Изменяет значение всех найденных вхождения old_value на new_value
	// Вернёт количество замен
	//Если old_value и new_value равны, вернет 0
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

#pragma region Cleaning

	// Удаление элемента с начала
	bool pop_back()
	{
		return remove_at(_nodesCount - 1);
	}

	// Удаление элемента с конца
	bool pop_front()
	{
		return remove_at(0);
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

#pragma endregion

};

#endif
