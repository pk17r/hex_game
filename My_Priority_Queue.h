#ifndef MY_PRIORITY_QUEUE_H_
#define	MY_PRIORITY_QUEUE_H_

#include <list>
#include "Node.h"

class MyPriorityQueue
{
public:
	MyPriorityQueue();
	~MyPriorityQueue();

	void push(Node node);

	Node* top();

	Node get_and_pop_top();

	bool contains_id(int id);

	Node* member_with_id(int id);

	void sort();

	int size_hex();

	void print();		//made for debugging usage

private:
	std::list<Node> my_list_;
};

#endif // !MY_PRIORITY_QUEUE_H_