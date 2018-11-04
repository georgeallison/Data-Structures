/* @author George Allison 
 * Date: 09/29/2016
 * Assignment 3
 * Course Instr. Elle Boese
 */ 
#include "HW3-Todo-StackArray.hpp"
#include <iostream>
using namespace std;

TodoStackArray::TodoStackArray()
{
	stackTop = -1;
}

bool TodoStackArray::isEmpty()
{
	if(stackTop == -1)
		return true;
	else
		return false;
}


bool TodoStackArray::isFull()
{
	if(stackTop == 4)
		return true;
	else
		return false;
}

void TodoStackArray::push(string todoItem)
{
	if(isFull())
	{
		cout << "Stack full, cannot add new todo item." << endl;
	}
	else
	{
		stackTop++;
		stack[stackTop] = new TodoItem;
		stack[stackTop]->todo = todoItem;
	}
}	

void TodoStackArray::pop()
{
	stackTop--;
}

TodoItem* TodoStackArray::peek()
{
	return stack[stackTop];
}



