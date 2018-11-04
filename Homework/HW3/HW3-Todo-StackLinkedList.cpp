/* @author George Allison 
 * Date: 09/29/2016
 * Assignment 3
 * Course Instr. Elle Boese
 */ 

#include "HW3-Todo-StackLinkedList.hpp"
#include <iostream>
using namespace std;

TodoStackLinkedList::TodoStackLinkedList()
{
	stackHead = NULL;
}

bool TodoStackLinkedList::isEmpty()
{
	if(stackHead == NULL)
		return true;
	else
		return false;
}


bool TodoStackLinkedList::isFull()
{
	//when is a linked list full? Other than memory limitations...?
	return false;
}

void TodoStackLinkedList::push(string todoItem)
{
	if(isFull())
	{
		cout << "Stack full, cannot add new todo item." << endl;
	}
	else
	{
		TodoItem *myItem = new TodoItem;
		myItem = stackHead;
		while(myItem->next)
		{
			myItem = myItem->next;
		}
		TodoItem *next = new TodoItem;
		myItem = next;
		myItem->todo = todoItem;
	}
}	

void TodoStackLinkedList::pop()
{
	if(stackHead->next)
	{
		TodoItem *prev = new TodoItem;
		TodoItem *temp = new TodoItem;
		prev = stackHead;
		temp = stackHead;
		while(temp->next != NULL)
		{
			prev = temp;
			temp = temp->next;
			temp = temp->next;
		}
		delete temp;
		prev->next = NULL;
	}
	else
	{
		cout << "Stack empty, cannot pop an item." << endl;
	}
}

TodoItem* TodoStackLinkedList::peek()
{
	TodoItem *myItem = new TodoItem;
	myItem = stackHead;
	while(myItem->next)
	{
		myItem = myItem->next;
	}
	return myItem;
}


