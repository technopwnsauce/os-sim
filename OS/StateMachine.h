#ifndef StateMachine
#define StateMachine
#include <iostream>

//int programNumber = 0;
extern int idmax;


struct preStateProcess {
	int entrypoint;
	int count;
	preStateProcess *previous;
	preStateProcess *next;
	int size;
	int ionumber;
	time_t runtime;

};

struct preStateList {
	preStateProcess *first;
	preStateProcess *current;
	preStateProcess *last;
};

	struct listProcess {                           //Basic List element
	int id;
	PCB *getPCB;
	listProcess *previous;
	listProcess *next;
};

	struct listStruct {                            //List Structure
	listProcess *first;
	listProcess *current;
	listProcess *last;
};

	extern listStruct newList;
	extern listStruct readyList;
	extern listStruct runningList;
	extern listStruct blockedList;
	extern listStruct doneList;


//void initializePreState();

void processTransferMain(listStruct*, listStruct*, PCB *);

int searchProcess(PCB*, listStruct*);               //Function prototypes

void swapList(listStruct*, listStruct*);

void firstElement(listStruct*, listStruct*);

void insertProcess(PCB*);

void newToReady(PCB*);

void readyToRunning(PCB*);

void runningToReady(PCB*);

void runningToBlocked(PCB*);

void blockedToReady(PCB*);

void runningToEnd(PCB*);

void printList(listStruct*, listStruct*);

void initFile();

void processInitializer();

void initializePCB();

void deleteElement();

void populateIO();

#endif