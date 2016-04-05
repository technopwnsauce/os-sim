#include <ctime>
#include <iostream>
#include "PCB.h"
#include "StateMachine.h"

using namespace std;

void insertProcess(PCB *Process) {
	//Initialize the process (I/O)
}

void searchProcess(PCB* sProcess, listStruct *old) {
	while (old->current->id != sProcess->returnId()) {
		old->current = old->current->next;
		if (old->current == NULL) {
			cout << "You're looking for a process that isn't in the list!";
			break;
		}
	}
}

void swapList(listStruct *old, listStruct *insert) {
		insert->last->next = newList.current;//This sets the last element in the new list to point to the new last element with its next pointer

		if (old->current->previous != NULL) {                 //These if statements check to see if the element is the first or last in the list
			old->current->previous->next = old->current->next;//These two assignments reattach the old list together after an element is taken from the middle

		}
		else
		{
			old->first = old->current->next;
		}                                                      //This sets the first value for the old list so we can take the element off the top safely
		if (old->current->next != NULL) {
			old->current->next->previous = old->current->previous;//

		}
		else
		{
			old->last = old->current->previous;
		}					                                  //This sets the last value for the old list so we can take the element off the bottom safely
		old->current->previous = insert->last;                //These two set the internal connections for our new last element in the new list
		old->current->next = NULL;                            //This is NULL because it's the last element

		insert->last = old->current;//The identity of our element is now (newList).last

		old->current = old->first;//Reset the old current value

		if (old->first == old->last) {                        //Takes into account the very last element in a list
			old->current->previous = NULL;
			old->current->next = NULL;
		}
}

void newToReady(PCB *Process) {
	Process->assignState(ready);
	if (readyList.first == NULL) {
		searchProcess(Process, newList);
		readyList.first = newList.current;
		readyList.current = readyList.first;
		readyList.last = readyList.first;
		swapList(newList, readyList);

	}
	else{
		searchProcess(Process, newList);
		swapList(newList, readyList);
	}
}

void readyToRunning(PCB *Process) {
	Process->assignState(running);
	if (runningList.first == NULL) {
		searchProcess(Process, readyList);
		runningList.first = readyList.current;
		runningList.current = runningList.first;
		runningList.last = runningList.first;
		swapList(readyList, runningList);

	}
	else {
		searchProcess(Process, readyList);
		swapList(readyList, runningList);
	}
}

void runningToReady(PCB *Process) {
	Process->assignState(ready);
	if (readyList.first == NULL) {
		searchProcess(Process, runningList);
		readyList.first = runningList.current;
		readyList.current = readyList.first;
		readyList.last = readyList.first;
		swapList(runningList, readyList);

	}
	else {
		searchProcess(Process, runningList);
		swapList(runningList, readyList);
	}
}

void runningToBlocked(PCB *Process) {
	Process->assignState(blocked);
	if (blockedList.first == NULL) {
		searchProcess(Process, runningList);
		blockedList.first = runningList.current;
		blockedList.current = blockedList.first;
		blockedList.last = blockedList.first;
		swapList(runningList, blockedList);

	}
	else {
		searchProcess(Process, runningList);
		swapList(runningList, blockedList);
	}
}

void blockedToReady(PCB *Process) {
	Process->assignState(ready);
	if (readyList.first == NULL) {
		searchProcess(Process, blockedList);
		readyList.first = blockedList.current;
		readyList.current = readyList.first;
		readyList.last = readyList.first;
		swapList(blockedList, readyList);

	}
	else {
		searchProcess(Process, blockedList);
		swapList(blockedList, readyList);
	}
}

void runningToEnd(PCB *Process) {
	Process->assignState(end);
	if (doneList.first == NULL) {
		searchProcess(Process, runningList);
		doneList.first = runningList.current;
		doneList.current = doneList.first;
		doneList.last = doneList.first;
		swapList(runningList, doneList);

	}
	else {
		searchProcess(Process, runningList);
		swapList(runningList, doneList);
	}
}
