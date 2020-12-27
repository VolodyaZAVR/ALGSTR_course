#include "Stack.h"
#include <sstream>
#include <stdlib.h>
using namespace std;


Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	while (top != nullptr)
		pop();
	delete top;
}

string Stack::getTop()
{
	if (!isEmpty())
	{
		return top->elem;
	}
	else
	{
		return nullptr;
	}
}

void Stack::push(string newElem)
{
	if (!isEmpty())
	{
		top = new StackNode(newElem, top);
	}
	else
	{
		top = new StackNode(newElem);
	}
}

string Stack::pop()
{
	string temp = top->elem;
	top = top->next;
	return temp;
}

bool Stack::isEmpty()
{
	if (top == nullptr)
		return true;
	else
		return false;
}