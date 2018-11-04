/*Homework 4
 * George Allison
 * CSCI 2270 Boese
 */
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include "MovieTree.hpp"
using namespace std;

int main(int argc, char** argv)
{	
	string myFile = argv[1];
	ifstream file;
	file.open(myFile);
	MovieTree tree;
	int ranking;
	string title;
	int year;
	int quantity;
	string line;
	string character;
	while(getline(file, line))
	{
		stringstream linestream(line);
		getline(linestream, character, ',');
		ranking = stoi(character);
		getline(linestream, title, ',');
		getline(linestream, character, ',');
		year = stoi(character);
		getline(linestream, character, ',');
		quantity = stoi(character);
		tree.addMovieNode(ranking, title, year, quantity);

	}
	file.close();
	
	bool quit = false;
	string s_input;
	int input;
	while(!quit)
	{
		cout << "======Main Menu======" << endl;
		cout << "1. Find a movie" << endl;
		cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl;
		cout << "4. Quit" << endl;
		getline(cin, s_input);
		input = stoi(s_input);
		string title = "";	
		
		switch(input)
		{
			case 1:
				cout << "Enter title:" << endl;
				getline(cin, title);
				tree.findMovie(title);
				break;
				
			case 2:
				cout << "Enter title:" << endl;
				getline(cin, title);
				tree.rentMovie(title);
				break;
			
			case 3:
				tree.printMovieInventory();
				break;
				
			case 4:
				cout << "Goodbye!" << endl; 
				quit = true;
				break;
			
			default:
				cout << "Invalid input" << endl;
				break;
		}
	}
	return 0;
}
