#include <ctime>
#include <iostream>
#include "PCB.h"
#include "StateMachine.h"

using namespace std;

void insertProcess(PCB *Process) {
	//Initialize the process (I/O)
}

int searchProcess(PCB* sProcess, listStruct *old) {        //Search for a process in a list
	while (old->current->id != sProcess->returnId()) {     //The while loop iterates through the specified list and looks for a matching id
		old->current = old->current->next;
		if (old->current == NULL) {                        //The if statement returns an error in the event that the correct process is not found
			cout << "You're looking for a process that isn't in the list!";
			return 1;
		}
		else
			return 0;
	}
	return 0;
}

void swapList(listStruct *old, listStruct *insert) {          //This function actually movies the processes from list to list

	    insert->last->next = newList.current;                 //This sets the last element in the new list to point to the new last element with its next pointer

		if (old->current->previous != NULL) {                 //These if statements check to see if the element is the first or last in the list
			old->current->previous->next = old->current->next;//These two assignments reattach the old list together after an element is taken from the middle

		}
		else
		{
			old->first = old->current->next;
		}                                                         //This sets the first value for the old list so we can take the element off the top safely
		if (old->current->next != NULL) {                         //This checks to make sure that the element we are removing isn't the last in the list
			old->current->next->previous = old->current->previous;//If not, set the next element's previous value to the urrent element's previous value

		}
		else
		{
			old->last = old->current->previous;               //If so, set the last value in the old list
		}					                                  //This sets the last value for the old list so we can take the element off the bottom safely
		old->current->previous = insert->last;                //These two set the internal connections for our new last element in the new list
		old->current->next = NULL;                            //This is NULL because it's the last element

		insert->last = old->current;                          //The identity of our element is now (newList).last

		old->current = old->first;                            //Reset the old current value

		if (old->first == old->last) {                        //Takes into account the very last element in a list
			old->current->previous = NULL;
			old->current->next = NULL;
		}
}
void processTransferMain(listStruct old, listStruct updateList, PCB *Process) {//Main body of the process transfer algorithm

	if (updateList.first == NULL) {                          //First we handle a empty list by checking to see if the first pointer is NULL
		if (searchProcess(Process, old) == 1)                 //If the process given isn't in the old list, return an error
			cout << "    ERROR";
		else
		{
			updateList.first = old.current;                //If the list is empty, populate the pointers
			updateList.current = updateList.first;
			updateList.last = updateList.first;
			swapList(old, updateList);                     //Swap in the new element
		}
	}
	else {                                                    //If the list isn't empty we do everything we did above besides populating the first, current, and last pointers
		if (searchProcess(Process, old) == 1)
			cout << "    ERROR";
		else
		{
			searchProcess(Process, old);
			swapList(old, updateList);
		}
	}
}

void newToReady(PCB *Process) {                               //New->Ready
	Process->assignState(ready);
	processTransferMain(newList, readyList, Process);
}

void readyToRunning(PCB *Process) {                           //Ready->Running
	Process->assignState(running);
	processTransferMain(readyList, runningList, Process);
}

void runningToReady(PCB *Process) {                           //Running->Ready
	Process->assignState(ready);
	processTransferMain(runningList, readyList, Process);
}

void runningToBlocked(PCB *Process) {                         //Running->Blocked
	Process->assignState(blocked);
	processTransferMain(runningList, blockedList, Process);
}

void blockedToReady(PCB *Process) {                           //Blocked->Ready
	Process->assignState(ready);
	processTransferMain(blockedList, readyList, Process);
}

void runningToEnd(PCB *Process) {                             //Running->End
	Process->assignState(endstate);
	processTransferMain(runningList, doneList, Process);
}

