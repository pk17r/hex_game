#include <algorithm>
#include <iostream>
#include <list>
#include "My_Priority_Queue.h"

using namespace std;

MyPriorityQueue::MyPriorityQueue()
{	
}

MyPriorityQueue::~MyPriorityQueue()
{
}

void MyPriorityQueue::push(Node node)
{
	my_list_.push_back(node);
	sort();
}

Node* MyPriorityQueue::top()
{
	return &(my_list_.front());
}

Node MyPriorityQueue::get_and_pop_top()
{
	auto node = my_list_.front();
	my_list_.pop_front();
	return node;
}

bool MyPriorityQueue::contains_id(int id)
{
	for (Node node : my_list_)
	{
		if (node.id == id)
			return true;
	}
	return false;
}

Node* MyPriorityQueue::member_with_id(int id)
{
	for (Node &node : my_list_)
	{
		if (node.id == id)
		{
			return &node;
		}
	}
	return nullptr;
}

void MyPriorityQueue::sort()
{
	auto cmpFn = [](Node left, Node right) {return left.id < right.id; };
	my_list_.sort(cmpFn);
}

int MyPriorityQueue::size_hex()
{
	return static_cast<int>(my_list_.size());
}

void MyPriorityQueue::print()
{
	cout << "Open Set: ";
	for_each(my_list_.cbegin(), my_list_.cend(), [](Node node) { cout << "\t(" << node.id << ")"; });
	cout << endl;
}
