/* @author George Allison 
 * Date: 09/29/2016
 * Assignment 3
 * Course Instr. Elle Boese
 */
#include "HW3-Todo-QueueArray.hpp"
#include <iostream>
using namespace std;

TodoQueueArray::TodoQueueArray()
{
	queueFront = -1;
	queueEnd = -1;
}

bool TodoQueueArray::isEmpty()
{
	for(int i=0; i<MAX_QUEUE_SIZE; i++) 
		if(queue[i] != NULL)
		{
			return false;
		}
	}
	return true;
}


bool TodoQueueArray::isFull()
{
	if(queueFront == 0 && queueEnd == MAX_QUEUE_SIZE - 1) 
	{
		return true;
	}
	if(queueEnd == queueFront - 1) 
	{
		return true;
	}
	return false;
}

void TodoQueueArray::enqueue(string todoItem)
{
	if(isFull())
	{
		cout << "Stack full, cannot add new todo item." << endl;
	}
	else
	{
		TodoItem *myItem = new TodoItem;
		myItem->todo = todoItem;
		if(queueEnd == MAX_QUEUE_SIZE)
		{
			queue[0] = myItem;
			queueEnd = 0;
		}
		else
		{
			queue[queueEnd + 1] = myItem; 
			queueEnd++;
		}
	}
}	

void TodoQueueArray::dequeue()
{
	if(isEmpty())
	{
		cout<<"Queue empty, cannot dequeue an item"<<endl;
	}
	else
	{
		if(queueEnd == 0)
		{
			queueEnd = MAX_QUEUE_SIZE;
		}
		else
		{
			queueEnd--;
		}
	}
}

TodoItem* TodoQueueArray::peek()
{
	if(isEmpty())
	{
		cout<<"Queue empty, cannot peek"<<endl;
		return NULL;
	}
	else
		return queue[queueEnd];
}
