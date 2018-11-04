#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "MovieTree.hpp"
using namespace std;

int main (int argc, char** argv)
{
	string argument = argv[1];
	ifstream file;
	file.open(argument);
	
	if (!file.is_open())
	{
		cout<<"file not found"<<endl;
		return 0;
	}
	
	int ranking;
	string title;
	int year;
	int quantity;
	
	MovieTree tree;
	
	string line;
	string character;
	
	while (getline(file, line))
	{
		stringstream lineStream(line);
		
		getline(lineStream, character, ',');
		ranking= stoi(character);
		
		getline(lineStream, title, ',');
		
		getline(lineStream, character, ',');
		year= stoi(character);
		
		getline(lineStream, character);
		quantity= stoi(character);
		
		tree.addMovieNode (ranking, title, year, quantity);
	}
	file.close();
	
	string user_command;
	
	string name;
	
    while (true) {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Count all movies" << endl;
        cout << "5. Delete a movie" << endl;
        cout << "6. Quit" << endl;
        getline(cin, user_command);
        switch (stoi(user_command)) 
        {
            case 1:
            {
                cout << "Enter title:" << endl;
                getline (cin, name);
                tree.findMovie(name);
                break;
            }
            case 2:
            {
                cout << "Enter title:" << endl;
                getline(cin,name);
                tree.rentMovie(name);
                break;
            }
            case 3:
            {
                tree.printMovieInventory();
                break;
            }
            case 4:
            {
				cout << "Counting Movies" << endl;
				cout<< tree.countMovieNodes() << endl;
				break;
			}
			case 5:
			{
				cout<< "Enter title:"<<endl;
				getline(cin,name);
				tree.deleteMovieNode(name);
				break;
			}
            case 6:
            {
                cout << "Goodbye!" << endl;
                return 0;
            }
            default:
            {
                cout << "Wrong choice detected, please choose again!" << endl;
            }
        }
    }
    return 0;
	
}
	
