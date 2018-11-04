#include "PatientQueue.hpp"
#include <iostream>

using namespace std;

PatientQueue::PatientQueue()
{
	for(int i = 0; i < 100; i++)
	{
		waitlist[i] = NULL;
	}
	lastIndex = 0;
}

int PatientQueue::size()
{
	return lastIndex;
}

bool PatientQueue::isEmpty()
{
	if(lastIndex <= 0)
	{
		return true;
	}
	return false;
}

void PatientQueue::enqueue(int priority, string name)
{
	Patient* MyPatient = new Patient(priority, name);
	cout << "Adding " << MyPatient->priority << " " << MyPatient->name << endl;
	lastIndex++;
	waitlist[lastIndex] = MyPatient;
	int i = lastIndex;
	while(i != 1)
	{
		if(waitlist[i]->priority < waitlist[i/2]->priority)//percolate up
		{
			swap(i, i/2);
			i = i/2;
		}
		else
		{
			break;
		}
	}
	printList();
}

Patient* PatientQueue::dequeue()
{
	cout << "Processing " << waitlist[1]->priority << " " << waitlist[1]->name << endl;
	Patient* temp = new Patient(waitlist[1]->priority, waitlist[1]->name);
	waitlist[1] = waitlist[lastIndex];
	int i = 1;
	if(lastIndex != 1)
	{
		while((i*2+1 < lastIndex) && (waitlist[i*2]->priority < waitlist[i]->priority || waitlist[(i*2)+1]->priority < waitlist[i]->priority))
		{
			if(waitlist[(i*2)+1]->priority < waitlist[i*2]->priority)
		{
			swap(i, (i*2)+1);
			i = i*2+1;
		}
		else
		{
			swap(i, (i*2));
			i = i*2;
		}
		}
	}
	lastIndex--;
	return temp;
}

void PatientQueue::printList()
{
  cout << "===" << endl << "Patients Waiting" << endl;
  if(isEmpty() != true)
  {
    for(int i = 1; i < lastIndex+1; i++)
    {
      cout << " [" << waitlist[i]->priority << "] " << waitlist[i]->name << endl;
    }
  }
  else
  {
    cout << "No one waiting!" << endl;
  }
  cout << "===" << endl;
}

void PatientQueue::swap(int index1, int index2)
{
    Patient* temp = waitlist[index1];
    waitlist[index1] = waitlist[index2];
    waitlist[index2] = temp;
}

PatientQueue::~PatientQueue()
{
  cout << "We're CLOSING! Deleting patient queue!" << endl;
  for(int i = 1; i < lastIndex+1; i++)
  {
    cout << "Removing " << waitlist[i]->name << " from the queue." << endl;
    delete waitlist[i];
  }
}
