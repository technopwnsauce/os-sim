#ifndef StateMachine
#define StateMachine
#include <iostream>
#include "PCB.h"

int programNumber = 0;

typedef struct listProcess {
	int id;
	listProcess *previous;
	listProcess *next;
};

typedef struct listStruct {
	listProcess *first;
	listProcess *current;
	listProcess *last;
};

listStruct newList = { NULL, NULL, NULL };
listStruct readyList = { NULL, NULL, NULL };
listStruct blockedList = { NULL, NULL, NULL };
listStruct runningList = { NULL, NULL, NULL };
listStruct doneList = { NULL, NULL, NULL };

void searchProcess(PCB*, listStruct);

void swapList(listStruct, listStruct);

void insertProcess(PCB*);

void newToReady(PCB*);

void readyToRunning(PCB*);

void runningToReady(PCB*);

void runningToBlocked(PCB*);

void blockedToReady(PCB*);

void runningToEnd(PCB*);

#endif