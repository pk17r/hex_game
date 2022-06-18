#include <algorithm>
#include <iostream>
#include "My_Priority_Queue.h"

using namespace std;

MyPriorityQueue::MyPriorityQueue()
{	
}

MyPriorityQueue::~MyPriorityQueue()
{
}

void MyPriorityQueue::capacity(int capacity)
{
	my_vec_.reserve(capacity);
}

void MyPriorityQueue::push(Node node)
{
	my_vec_.emplace_back(node);
	sort();
}

Node MyPriorityQueue::get_and_pop_top()
{
	auto node = my_vec_.front();
	my_vec_.erase(my_vec_.begin());
	return node;
}

bool MyPriorityQueue::contains_id(int id)
{
	for (Node &node : my_vec_)
	{
		if (node.id == id)
			return true;
	}
	return false;
}

Node* MyPriorityQueue::member_with_id(int id)
{
	for (Node &node : my_vec_)
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
	//my_vec_.sort(cmpFn);
	std::sort(my_vec_.begin(), my_vec_.end(), cmpFn);
}

void MyPriorityQueue::clear()
{
	my_vec_.clear();
}

int MyPriorityQueue::size()
{
	return static_cast<int>(my_vec_.size());
}

void MyPriorityQueue::print()
{
	cout << "Open Set: ";
	for_each(my_vec_.cbegin(), my_vec_.cend(), [](Node node) { cout << "\t(" << node.id << ")"; });
	cout << endl;
}
