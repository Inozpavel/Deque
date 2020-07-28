#ifndef DEQUE_H
#define DEQUE_H

template <typename T>
class Deque
{
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
public:
};

#endif
