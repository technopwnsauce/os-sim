#ifndef StateMachine
#define StateMachine
#include <iostream>
#include "PCB.h"

int programNumber = 0;

	struct listProcess {                           //Basic List element
	int id;
	listProcess *previous;
	listProcess *next;
};

	struct listStruct {                            //List Structure
	listProcess *first;
	listProcess *current;
	listProcess *last;
};

listStruct newList = { NULL, NULL, NULL };         //List Instances
listStruct readyList = { NULL, NULL, NULL };
listStruct blockedList = { NULL, NULL, NULL };
listStruct runningList = { NULL, NULL, NULL };
listStruct doneList = { NULL, NULL, NULL };

void processTransferMain(listStruct*, listStruct*, PCB *);

int searchProcess(PCB*, listStruct*);               //Function prototypes

void swapList(listStruct*, listStruct*);

void insertProcess(PCB*);

void newToReady(PCB*);

void readyToRunning(PCB*);

void runningToReady(PCB*);

void runningToBlocked(PCB*);

void blockedToReady(PCB*);

void runningToEnd(PCB*);

#endif