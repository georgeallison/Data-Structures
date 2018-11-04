// ==========================================
// File: HW2-LinkedListsNetwork.cpp
// Author: George Allison, Matt Bubernak(student started code)
// Date: 9/22/2016
// Description: Create, traverse, add, and delete to/from a linked-list
// ==========================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct city
{
    string 	name; 			// name of the city
    city 	*next; 			// pointer to the next city
	int 	numberMessages;	// how many messages passed through this city
    string 	message; 		// message we are sending accross
};

city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string filename);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
    // pointer to the head of our network of cities
    city *head = NULL;

	head = handleUserInput(head);
	printPath(head);
	head = deleteEntireNetwork(head);
	if (head == NULL)
		cout << "Path cleaned" << endl;
	else
		printPath(head);

	cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head the start of the linked list
 * @return the start of the linked list
 * Do NOT modify
 */
city* handleUserInput(city *head)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

		// read in input, assuming a number comes in
        getline(cin, s_input);
		input = stoi(s_input);

        switch (input)
        {
            // print all nodes
            case 1: 	//rebuild network
                head = loadDefaultSetup(head);
                printPath(head);
                break;

            case 2:		// print path
                printPath(head);
                break;

            case 3: //message is read in from file
			  {
        		string cityReceiver;
				cout << "Enter name of the city to receive the message: " << endl;
				getline(cin, cityReceiver);

				cout << "Enter the message to send: " << endl;
				string message;
				getline(cin, message);

                transmitMsg(head, cityReceiver, message);
			  }
                break;

            case 4:
			  {		//add city
        		string newCityName;
        		string prevCityName;
                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);

                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);

                // find the node containing prevCity
    			city *tmp = NULL;
                if(prevCityName !="First")
                    tmp = searchNetwork(head, prevCityName);
                // add the new node
                head = addCity(head, tmp, newCityName);
                printPath(head);
			  }
                break;

            case 5: 	// delete city
			  {
        		string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                head = deleteCity(head, city);
                printPath(head);
			  }
                break;

            case 6: 	// delete network
                head = deleteEntireNetwork(head);
                break;

            case 7: 	// quit
                quit = true;
				cout << "Quitting... cleaning up path: " << endl;
                break;

            default: 	// invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
	return head;
}

/* 
 * Purpose: Add a new city to the network 
 *   between the city *previous and the city that follows it in the network. 
 * @param head pointer to start of the list
 * @param previous name of the city that comes before the new city
 * @param cityName name of the new city
 * @return pointer to first node in list
 */
city* addCity(city *head, city *previous, string cityName)
{
	if(previous == NULL)
	{
		city *adder = new city;
		adder->next = NULL;
		adder->name = cityName;
		if(head == NULL){
			head = new city;
		}
		previous = head;
		head->next = adder;
	}
	else
	{
		city *adder = new city;
		city *temp = new city;
		temp = NULL;
		if(previous->next != NULL)
		{
			temp = previous->next;
		}
		previous->next = adder;
		adder->next = temp;
		adder->name = cityName;
	}
	
	cout << "prev: " << previous->name << "  new: " << cityName << endl; //keep
    return head;
}


/*
 * Purpose: Search the network for the specified city and return a pointer to that node
 * @param ptr head of the list
 * @param cityName name of the city to look for in network
 * @return pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city *searchNetwork(city *ptr, string cityName)
{
	bool found = false;
	while(ptr->next != NULL && found == false)
	{
		if(ptr->name == cityName)
		{
			found = true;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	return ptr;
}

/*
 * Purpose: deletes all cities in the network starting at the head city. 
 * @param ptr head of list
 * @return NULL as the list is empty
 */
city* deleteEntireNetwork(city *ptr)
{	
	if(ptr != NULL)
	{
		city *temp = ptr->next;
		while(temp->next != NULL)
		{
			city *old = temp;
			temp = temp->next;
			cout << "deleting: " << ptr->name << endl;
			delete old;
		}
	}
	cout << "Deleted network" << endl;
    // return head, which should be NULL
    return ptr;
}

/* sends messages from file */
void transmitMsg(city *head, string receiver, string message)
{
	
	city *sender = new city;
	sender = head;
    if(head == NULL)
	{
        cout << "Empty list" << endl;
        return;
    }
    else
    {	
		sender = sender->next;//easy solution for cout starting at head
		bool loc = false;
		while(loc ==  false)
		{	
			sender->message = message;
			sender->numberMessages++;
			cout << sender->name << " [# messages passed: " << sender->numberMessages << "] received: " << sender->message << endl;
			if(sender->name == receiver)
			{
				loc = true;
			}
			sender = sender->next;
		}
	}

}


/* 
 * Purpose: delete the city in the network with the specified name. 
 * @param head first node in list
 * @param cityName name of the city to delete in the network
 * @return head node of list 
 */
city* deleteCity(city *head, string cityName)
{
	city *temp1;
	city *temp2;
	temp1 = head;
	bool exists = false;
	while(temp1->next != NULL)
	{
		temp2 = temp1->next;
		if(temp2->name == cityName)
		{
			temp1->next = temp2->next;
			exists = true;
		}
		else
		{
			temp1 = temp2;
		}
	}
    // if the city dosn't exist, nothing we can do.
	// 		use this output statement
	if(exists == false)
        cout << "City does not exist." << endl;



    return head;
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void printPath(city *ptr)
{
    cout << "\n== CURRENT PATH ==" << endl;

    // If the head is NULL
    if (ptr == NULL)
        cout << "nothing in path" << endl;
    else
    {
		while(ptr->next != NULL)
		{
			cout << ptr->name << " -> ";
			ptr = ptr->next;
		}
		cout << ptr->name; // last city
	}

    cout << "===\n" << endl;
}

/* 
 * Purpose: populates the network with the predetermined cities 
 * @param head start of list
 * @return head of list
 */
city* loadDefaultSetup(city *head)
{
	city *tmp = new city;
    head = deleteEntireNetwork(head);
    head = addCity(head,NULL,"Los Angeles");
    tmp = searchNetwork(head, "Los Angeles");
    head = addCity(head, tmp, "Denver");
    tmp = searchNetwork(head, "Denver");
    head = addCity(head, tmp, "Dallas");
    tmp = searchNetwork(head, "Dallas");
    head = addCity(head, tmp, "Atlanta");
    tmp = searchNetwork(head, "Atlanta");
    head = addCity(head, tmp, "New York");
    return head;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
	cout << "\nSelect a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit\n" << endl;
}


