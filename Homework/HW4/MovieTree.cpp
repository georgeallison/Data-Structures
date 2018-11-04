/*Homework 4
 * George Allison
 * CSCI 2270 Boese
 */
#include "MovieTree.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

MovieTree::MovieTree()
{
	root = NULL;
}
MovieTree::~MovieTree()
{
	//dtor
}

void MovieTree:: printMovieInventory()	
{
	printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode *node)
{
	if(node != NULL)
	{
		printMovieInventory(node->leftChild);
		cout << node->title << " " << node->quantity << endl;
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
	MovieNode *myNode = new MovieNode;
	myNode->ranking = ranking;
	myNode->title = title;
	myNode->year = releaseYear;
	myNode->quantity = quantity;
	myNode->leftChild = NULL;
	myNode->rightChild = NULL;
	
	if(root == NULL)
	{
		root= myNode;
	}
	else
	{
		MovieNode* search = root;
		MovieNode* searchparent = root;
		
		while ( search != NULL)
		{
			searchparent=search;
			
			if (myNode->title.compare(search->title)<0)
			{
				search=search->leftChild;
			}
			else 
			{
				search=search->rightChild;
			}
		}
		
		myNode->parent=searchparent;
		if (myNode->title.compare(searchparent->title)<0)
		{
			searchparent->leftChild=myNode;
		}
		else
		{
			searchparent->rightChild=myNode;
		}
	}
}

void MovieTree::findMovie(string title)
{
	MovieNode* myNode = search (title);
	if (myNode==NULL)
	{
		cout<< "Movie not found" << endl;
	}
	else
	{
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << myNode->ranking << endl;
		cout << "Title:" << myNode->title << endl;
		cout << "Year:" << myNode->year << endl;
		cout << "Quantity:" << myNode->quantity << endl;
	}
}

void MovieTree::rentMovie(string title)
{
	MovieNode* myNode = search (title);
	if (myNode==NULL)
	{
		cout<< "Movie not found." << endl;
	}
	else if (myNode->quantity == 0)
	{
		cout<< "Movie out of stock.";
	}
	else
	{
		myNode->quantity = (myNode->quantity) - 1;
		cout << "Movie has been rented!" << endl;
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << myNode->ranking << endl;
		cout << "Title:" << myNode->title << endl;
		cout << "Year:" << myNode->year << endl;
		cout << "Quantity:" << myNode->quantity << endl;
	}
}

MovieNode* MovieTree::search(string title)
{
	MovieNode* myNode = root;
	while (myNode!=NULL)
	{
		if (!myNode->title.compare(title))
		{
			return myNode;
			break;
		}
		else if( myNode->rightChild==NULL && myNode->leftChild==NULL)
		{
			return NULL;
			break;
		}
		else if ( myNode->title.compare(title) > 0)
		{
			myNode=myNode->leftChild;
		}	
		else
		{
			myNode=myNode->rightChild;
		}
	}	
	return myNode;
}
