#include <ctime>
#include <iostream>
#include "PCB.h" 
#include "StateMachine.h"

using namespace std;

/*void insertProcess(PCB *Process) {
	//Initialize the process (I/O)
}*/

int searchProcess(PCB* sProcess, listStruct *old) {                                        //Search for a process in a list
	old->current = old->first;
	if (old->current == NULL) {                                                            //The if statement returns an error in the event that the list is empty
		cout << "This list is empty!";
		return 1;
	}
	else {
		while (old->current->id != sProcess->returnId()) {                                 //The while loop iterates through the specified list and looks for a matching id
			if (old->current->next == NULL) {                                              //The if statement returns an error in the event that the correct process is not found
				cout << "You're looking for a process that isn't in the list!";
				return 1;
			}
			else
				old->current = old->current->next;
		}
		return 0;
	}
}

void swapList(listStruct *old, listStruct *insert) {                                        //This function actually moves the processes from list to list
		if (old->current->previous != NULL && old->current->next != NULL) {                 //These if statements check to see if the element is the first, last, or very last in the list
			old->current->previous->next = old->current->next;                              //These two assignments reattach the old list together after an element is taken from the middle
			old->current->next->previous = old->current->previous;
		}

		else
		{
			if (old->current->previous == NULL && old->current->next == NULL) {             //Very last element in the old list
				old->first = NULL;
				old->last = NULL;
			}
			else {
				if (old->current->previous == NULL) {                                       //First element in the old list
					old->first = old->current->next;
					old->current->next->previous = NULL;
				}
				if (old->current->next == NULL) {                                           //Last element in the old list
					old->last = old->current->previous;
					old->current->previous->next = NULL;
				}
			}
		}                                             
		
		old->current->previous = insert->last;                                              //These two set the internal connections for our new last element in the new list
		old->current->next = NULL;                                                          //This is NULL because it's the last element

		insert->last->next = old->current;                                                  //Connects the new element to the end of the new list

		insert->last = old->current;                                                        //The identity of our element is now (newList).last

		old->current = old->first;                                                          //Reset the old current value

}

void firstElement(listStruct *old, listStruct *insert) {                                    //This prepares an empty list for a first element
	insert->first = old->current;                                                           //If the list is empty, populate the pointers
	insert->current = insert->first;
	insert->last = insert->first;

	if (old->current->previous != NULL && old->current->next != NULL) {                     //These if statements check to see if the element is the first or last in the list
		old->current->previous->next = old->current->next;                                  //These two assignments reattach the old list together after an element is taken from the middle
		old->current->next->previous = old->current->previous;
	}

	else
	{
		if (old->current->previous == NULL) {                                               //Handles first and last elements the same way swapList does
			old->first = old->current->next;
			old->current->next->previous = NULL;
		}
		if (old->current->next == NULL) {
			old->last = old->current->previous;
			old->current->previous->next = NULL;
		}
	}

	old->current->previous = NULL;                                                          //Sets the internal values for the new list
	old->current->next = NULL;
	old->current = old->first;                                                              //Resets old current value
}

void processTransferMain(listStruct *old, listStruct *updateList, PCB *Process) {           //Main body of the process transfer algorithm

	if (updateList->first == NULL) {                                                        //First we handle a empty list by checking to see if the first pointer is NULL
		if (searchProcess(Process, old) == 1)                                               //If the process given isn't in the old list, return an error
			cout << "    ERROR\n";
		else
		{
			firstElement(old, updateList);                                                  //This handles the case an empty new list
		}
	}
	else {                                                                                
		if (searchProcess(Process, old) == 1)
			cout << "    ERROR";
		else
		{
			swapList(old, updateList);                                                      //In the case of a non-empty target list, tranfers the process
		}
	}
}

void newToReady(PCB *Process) {                               //New->Ready
	Process->assignState(ready);
	processTransferMain(&newList, &readyList, Process);
}

void readyToRunning(PCB *Process) {                           //Ready->Running
	Process->assignState(running);
	processTransferMain(&readyList, &runningList, Process);
}

void runningToReady(PCB *Process) {                           //Running->Ready
	Process->assignState(ready);
	processTransferMain(&runningList, &readyList, Process);
}

void runningToBlocked(PCB *Process) {                         //Running->Blocked
	Process->assignState(blocked);
	processTransferMain(&runningList, &blockedList, Process);
}

void blockedToReady(PCB *Process) {                           //Blocked->Ready
	Process->assignState(ready);
	processTransferMain(&blockedList, &readyList, Process);
}

void runningToEnd(PCB *Process) {                             //Running->End
	Process->assignState(endstate);
	processTransferMain(&runningList, &doneList, Process);
}

void printList(listStruct * oldStruct, listStruct * newStruct) {                         //This is a useful debug function which prints lists. Can be modified
	cout << "\n";
	oldStruct->current = oldStruct->first;                                               //Resets current values for incrementing
	newStruct->current = newStruct->first;
	while (oldStruct->current != NULL) {                                                 //runs until current gets to the end of the list
		cout << oldStruct->current->id << "\n";                                          //prints ids
		oldStruct->current = oldStruct->current->next;
	}
	cout << "\nold^\n";
	while (newStruct->current != NULL) {                                                 //Does another list. Was used for checking list states of two lists after a transfer between them occured
		cout << newStruct->current->id << "\n";
		newStruct->current = newStruct->current->next;
	}
	cout << "\nnew^\n\n";
}

