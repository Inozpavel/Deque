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
	bool _remove_node(Node* node);
	Node* _search(T value, Node* element = nullptr);
	Node* _search_last(T value, Node* element = nullptr);
	Node* _getElement(unsigned index);

public:

	static unsigned const NOT_FOUND = ~0;

	Deque();

	void insert(T element, unsigned pos);

	void push_front(T element);

	void push_back(T element);

	bool pop_back();

	bool pop_front();

	T& operator[](unsigned index);

	void swap(unsigned firstPos, unsigned secondPos);

	bool remove(T value);

	bool remove_last(T value);

	bool remove_at(unsigned pos);

	unsigned remove_all(T value);

	unsigned find(T value, unsigned startPos = 0);

	unsigned find_last(T value, unsigned startPos);

	vector<unsigned> find_all(T value);

	bool update(T oldValue, T newValue);

	bool update_last(T oldValue, T newValue);

	unsigned update_all(T oldValue, T newValue);

	unsigned size();

	void print_all(bool reverse = false);

	void erase(unsigned start, unsigned stop);

	void erase(unsigned start);

	void clear();

	~Deque();
};

#endif
