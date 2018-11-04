
#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

MovieTree::MovieTree()
{
	root=NULL;
}

MovieTree::~MovieTree()
{
	DeleteAll(root);
}

void MovieTree:: addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
	if (root==NULL)
	{
		root= new MovieNode;
		root->ranking=ranking;
		root->title=title;
		root->year=releaseYear;
		root->quantity=quantity;
		root->leftChild=NULL;
		root->rightChild=NULL;
		return;
	}
	MovieNode* tmp= new MovieNode;
	tmp->ranking=ranking;
	tmp->title=title;
	tmp->year=releaseYear;
	tmp->quantity=quantity;
	tmp->rightChild=NULL;
	tmp->leftChild=NULL;

	MovieNode* search= root;
	MovieNode* searchparent= root;

	while ( search!= NULL)
	{
		searchparent=search;

		if (tmp->title.compare(search->title)<0)
		{
			search=search->leftChild;
		}
		else
		{
			search=search->rightChild;
		}
	}

	tmp->parent=searchparent;
	if (tmp->title.compare(searchparent->title)<0)
	{
		searchparent->leftChild=tmp;
	}
	else
	{
		searchparent->rightChild=tmp;
	}
}

void MovieTree:: printMovieInventory()
{
	printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode* node)
{
	if(node!=NULL)
	{
	printMovieInventory(node->leftChild);
	cout<<node->title<<" "<<node->quantity<<endl;
	printMovieInventory(node->rightChild);
	}
}

void MovieTree::findMovie(string title)
{
	MovieNode* tmp2 = search (title);
	if (tmp2==NULL)
	{
		cout<< "Movie not found"<<endl;
	}
	else
	{


	cout << "Movie Info:" << endl;

	cout << "===========" << endl;

	cout << "Ranking:" << tmp2->ranking << endl;

	cout << "Title:" << tmp2->title << endl;

	cout << "Year:" << tmp2->year << endl;

	cout << "Quantity:" << tmp2->quantity << endl;
	}
}

void MovieTree::rentMovie(string title)
{
	MovieNode* tmp2 = search (title);
	if (tmp2==NULL)
	{
		cout<< "Movie not found"<<endl;
	}


	else
	{
	if (tmp2->quantity==0)
	{
		cout<<"Movie out of Stock"<<endl;
		return;
	}

	else
	{
	tmp2->quantity=tmp2->quantity-1;

	cout<<"Movie has been rented"<<endl;

	cout << "Movie Info:" << endl;

	cout << "===========" << endl;

	cout << "Ranking:" << tmp2->ranking << endl;

	cout << "Title:" << tmp2->title << endl;

	cout << "Year:" << tmp2->year << endl;

	cout << "Quantity:" << tmp2->quantity << endl;
	}

	}
}

MovieNode* MovieTree::search(string title)
{
	MovieNode* temp = root;
	while (temp!=NULL)
	{
		if (!temp->title.compare(title))
		{
			return temp;
			break;
		}
		else if( temp->rightChild==NULL && temp->leftChild==NULL)
		{
			return NULL;
			break;
		}
		else if ( temp->title.compare(title) > 0)
		{
			temp=temp->leftChild;
		}

		else
		{
			temp=temp->rightChild;
		}
	}

	return temp;
}

void MovieTree::deleteMovieNode(string title)
{
    MovieNode *node = search(title);
    if(node != NULL)
	{
        if(node->leftChild == NULL && node->rightChild == NULL) //No children
        {
            if(node->parent->leftChild == node)//node is a left child
            {
                node->parent->leftChild = NULL;
            }
            else//node is a right child
                node->parent->rightChild = NULL;
            delete node;
        }
        else if(node->rightChild == NULL)//Only has left child
        {
            if(node->parent->leftChild == node)//node is a left child
            {
                node->parent->leftChild = node->leftChild;
            }
            else//node is a right child
            {
                node->parent->rightChild = node->leftChild;
            }
            delete node;
        }
        else if(node->leftChild == NULL)//Only has right child
        {
            if(node->parent->rightChild == node)//node is a right child
            {
                node->parent->rightChild = node->rightChild;
            }
            else//node is a left child
            {
                node->parent->leftChild = node->rightChild;
            }
            delete node;
        }

        else// has two children
        {
            MovieNode* temp = treeMinimum(node);
            node->title = temp->title;
            node->quantity = temp->quantity;
            node->ranking = temp->ranking;
            node->year = temp->year;
            if(temp->rightChild != NULL)
            {
                temp->rightChild->parent = temp->parent;
            }
            if(temp->parent->leftChild == temp)
            {
                temp->parent->leftChild == temp->rightChild;
            }
            else
            {
                temp->parent->rightChild = temp->rightChild;
            }
            delete temp;
		}
		cout << title << " has been deleted" << endl;
	}
	else
	{
		cout<< "\"" << title << "\" not found"<<endl;
	}
}

MovieNode* MovieTree::treeMinimum(MovieNode *node)
{
	MovieNode* minNode = node->rightChild;
	while(minNode->leftChild != NULL)
	{
		minNode = minNode->leftChild;
	}
	return minNode;
}

int MovieTree::countMovieNodes()
{
	int c = 0;
	int *ptrC;
	ptrC = &c;
	countMovieNodes(root, ptrC);
	int val = *ptrC;
	return val;
}

void MovieTree::countMovieNodes(MovieNode *node, int * c)
{

	if(node != NULL)
	{
		*c += 1;
		countMovieNodes(node->leftChild, c);
		countMovieNodes(node->rightChild, c);
	}
}

void MovieTree::DeleteAll(MovieNode* node)
{
	if(node != NULL)
	{
		DeleteAll(node->leftChild);
		DeleteAll(node->rightChild);
		delete node;
	}
}
