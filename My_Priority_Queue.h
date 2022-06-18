#ifndef MY_PRIORITY_QUEUE_H_
#define	MY_PRIORITY_QUEUE_H_

#include <vector>
#include "Node.h"

class MyPriorityQueue
{
public:
	MyPriorityQueue();

	~MyPriorityQueue();

	void capacity(int capacity);

	void push(Node node);

	Node get_and_pop_top();

	bool contains_id(int id);

	Node* member_with_id(int id);

	void sort();

	void clear();

	int size();

	void print();		//made for debugging usage

	std::vector<Node> my_vec_;
};

#endif // !MY_PRIORITY_QUEUE_H_