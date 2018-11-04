/* @author George Allison 
 * Date: 09/29/2016
 * Assignment 3
 * Course Instr. Elle Boese
 */ 
#include "HW3-Todo-QueueLinkedList.hpp"
#include <iostream>
using namespace std;

TodoQueueLinkedList::TodoQueueLinkedList()
{
	queueFront = NULL;
	queueEnd = NULL;
}

bool TodoQueueLinkedList::isEmpty()
{
	if(queueFront==NULL)
		return true;
	else
		return false;
}	


bool TodoQueueLinkedList::isFull()
{
	//when is a linked list full? Other than memory limitations...?
	return false;
}

void TodoQueueLinkedList::enqueue(string todoItem)
{
	if(queueEnd == NULL && queueFront == NULL)
	{
		queueFront = new TodoItem;
		queueFront->todo = todoItem;
		queueEnd = queueFront;
	}
	else if(queueFront==queueEnd && queueFront != NULL)
	{
		queueEnd = new TodoItem;
		queueEnd->todo=todoItem;
		queueFront->next = queueEnd;
	}
	else if(queueFront!=queueEnd)
	{
		TodoItem* tmp=new TodoItem;
		queueEnd->next=tmp;
		queueEnd=queueEnd->next;
	}
}	

void TodoQueueLinkedList::dequeue()		
{
	if (queueFront==NULL && queueEnd==NULL)
	{
		cout<<"Queue empty, cannot dequque an item."<<endl;
	}
	
	else if (queueFront==queueEnd && queueFront!=NULL)
	{
		delete (queueFront);
		queueFront=NULL;
		queueEnd=NULL;
	}
	
	else if (queueFront!=queueEnd)
	{
		TodoItem* tmp=queueFront;
		delete (tmp);
		queueFront=queueFront->next;
		
	}
}

TodoItem* TodoQueueLinkedList::peek()
{
	return queueFront;
}




