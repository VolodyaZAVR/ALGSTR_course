#pragma once
#include <sstream>
#include <stdlib.h>
using namespace std;

class Stack {
private:
	class StackNode {
	public:
		StackNode(string elem, StackNode* next = nullptr)
		{
			this->elem = elem;
			this->next = next;
		}
		~StackNode() {};

		string elem;
		StackNode* next;
	};
	StackNode* top;
public:
	Stack();
	~Stack();
	string getTop();
	void push(string);
	string pop();
	bool isEmpty();
};