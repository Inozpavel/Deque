#ifndef DEQUE_H
#define DEQUE_H

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

		Node(T data, Node* next = nullptr, Node* previous = nullptr) :
			data(data), next(next), previous(previous)
		{
		}
	};
	Node* _head;
	Node* _tail;
	unsigned _nodesCount;

	// Удаляет элемент, сохраняя целосность списка
	bool _remove_node(Node* node);

	// Ищет первый Node, данные в котором равны value
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _search(T value, Node* element = nullptr);

	// Ищет последний Node, данные в котором равны value
	// Возвращает указатель на него в случае успеха, иначе nullptr
	Node* _search_last(T value, Node* element = nullptr);

	// Ищет элемент по индексу
	// В стучае успеха возвращает указатель на него, иначе nullptr
	Node* _get_element(unsigned index);

public:

	static unsigned const NOT_FOUND = ~0;

	Deque();

	// Добавление элемента на указанную позицию
	void insert(T element, unsigned pos);

	// Добавление элемента в начало
	void push_front(T element);

	// Добавление элемента в конец
	void push_back(T element);

	// Удаление элемента с начала
	bool pop_back();

	// Удаление элемента с конца
	bool pop_front();

	// Оператор [ ] позволяет по индексу получить ссылку на элемент списка
	T& operator[](unsigned index);

	// Обмен местами элементов first и second
	void swap(unsigned firstPos, unsigned secondPos);

	// Удаление одного (первого) элемента по значению value
	// Вернёт true в случае успеха (нашёл)
	bool remove(T value);

	// Удаление последнего элемента по значению value
	// Вернёт true в случае успеха (нашёл)
	bool remove_last(T value);

	// Удаление элемента на позиции pos
	bool remove_at(unsigned pos);

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
	unsigned size();

	// Выводит список на экран
	void print_all(bool reverse = false);

	// Удаляет все элементы из [start; stop]
	void erase(unsigned start, unsigned stop);

	// Удаляет все элементы начиная со start
	void erase(unsigned start);

	// Очищает весь список
	void clear();

	// Очистка памяти, удаление списка
	~Deque();
};

#endif
