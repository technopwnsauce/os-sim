/*
 * main.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: kylearchuleta
 */

#include <iostream>
#include <ctime>
#include <limits>
#include <string>
#include "PCB.h"
#include "StateMachine.h"
#include "LowLevelScheduler.h"
#include "HighLevelScheduler.h"

listStruct newList = { NULL, NULL, NULL };         //List Instances
listStruct readyList = { NULL, NULL, NULL };
listStruct blockedList = { NULL, NULL, NULL };
listStruct runningList = { NULL, NULL, NULL };
listStruct doneList = { NULL, NULL, NULL };
bool statechange = 0;
int idmax = 0;
PageTable pTable;
bool memory[MEMSIZE] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};
LowLevelScheduler lowlevel = LowLevelScheduler();
 
using namespace std;

void highMain(int);
void runFunc();
void printstuff();
int sizeofList2(listStruct);
listProcess *tempproc = NULL;

int main(void){ //main function - the OS simulator
	//initialization
	bool done = 0;
	srand(time(NULL));
	clock_t hold;
	initFile();
	while (!done) {
		processInitializer();//Watch the skipping new problem
		//highlevelscheduler
		if (newList.first != NULL) {
			tempproc = newList.first;
			while (tempproc != NULL) {
				highMain(tempproc->id);
				tempproc = tempproc->next;
			}
			tempproc = newList.first;
		}
								   //run
		lowlevel.decrementIO();
		runFunc();              //timeslice?
		if (statechange) {
			printstuff();
			//hold = clock() + 1*CLOCKS_PER_SEC;
			//cout << &readyList.current->next << endl;
		//	while (clock() < hold) {};
		}
		// All under loop indicating change in state machine 
		statechange = 0;
	}
	return 0;
}

void printstuff() {
	system("cls");

	// All under loop indicating change in state machine 
	// State Change Flag
	bool stateChange = false; //fix to take value from Brian

							  ////////////////////////////Print out memory bar
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << "\t" << pTable.processID[0] << "\t" << "|" << "\t" << pTable.processID[1] << "\t" << "|" << "\t" << pTable.processID[2] << "\t" << "|" << "\t" << pTable.processID[3] << "\t" << "|" << "\t" << pTable.processID[4] << "\t" << "|" << "\t" << pTable.processID[5] << "\t" << "|" << "\t" << pTable.processID[6] << "\t" << "|" << "\t" << pTable.processID[7] << "\t" << "|" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " " << "\t" << 0 << "\t" << " " << "\t" << 1 << "\t" << " " << "\t" << 2 << "\t" << " " << "\t" << 3 << "\t" << " " << "\t" << 4 << "\t" << " " << "\t" << 5 << "\t" << " " << "\t" << 6 << "\t" << " " << "\t" << 7 << "\t" << " " << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << "\t" << pTable.processID[8] << "\t" << "|" << "\t" << pTable.processID[9] << "\t" << "|" << "\t" << pTable.processID[10] << "\t" << "|" << "\t" << pTable.processID[11] << "\t" << "|" << "\t" << pTable.processID[12] << "\t" << "|" << "\t" << pTable.processID[13] << "\t" << "|" << "\t" << pTable.processID[14] << "\t" << "|" << "\t" << pTable.processID[15] << "\t" << "|" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " " << "\t" << 8 << "\t" << " " << "\t" << 9 << "\t" << "|" << "\t" << 10 << "\t" << " " << "\t" << 11 << "\t" << " " << "\t" << 12 << "\t" << "|" << "\t" << 13 << "\t" << " " << "\t" << 14 << "\t" << " " << "\t" << 15 << "\t" << " " << endl;

	cout << "\n" << "\n" << "\n";

	/////////////////////////////Print out of process in each state
	// Print New
	cout << "New" << endl;
	int newSize = sizeofList2(newList);
	string newPrint = "";
	for (int i = 0; i < newSize; i++)
	{
		newPrint = newPrint + "|" + std::to_string(newList.current->getPCB->returnId());
		newList.current = newList.current->next;
	}
	newList.current = newList.first; // Reset pointer
	cout << newPrint << endl;
	cout << "" << endl;

	// Print Ready
	cout << "Ready" << endl;
	int readySize = sizeofList2(readyList);
	string readyPrint="";
	for (int i = 0; i < readySize; i++)
	{
		readyPrint = readyPrint + "|" + std::to_string(readyList.current->getPCB->returnId());
		readyList.current = readyList.current->next;
	}
	readyList.current = readyList.first; // Reset pointer
	cout << readyPrint << endl;
	cout << "" << endl;

	// Print Running
	cout << "Running" << endl;
	int runningSize = sizeofList2(runningList);
	string runningPrint="";
	for (int i = 0; i < runningSize; i++)
	{
		runningPrint = runningPrint + "|" + std::to_string(runningList.current->getPCB->returnId());
		runningList.current = runningList.current->next;
	}
	runningList.current = runningList.first; // Reset pointer
	cout << runningPrint << endl;
	cout << "" << endl;

	// Print Blocked
	cout << "Blocked" << endl;
	int blockedSize = sizeofList2(blockedList);
	string blockedPrint="";
	for (int i = 0; i < blockedSize; i++)
	{
		blockedPrint = blockedPrint + "|" + std::to_string(blockedList.current->getPCB->returnId());
		blockedList.current = blockedList.current->next;
	}
	blockedList.current = blockedList.first; // Reset pointer
	cout << blockedPrint << endl;
	cout << "" << endl;

	// Print Exit
	cout << "Exit" << endl;
	int doneSize = sizeofList2(doneList);
	string donePrint="";
	for (int i = 0; i < doneSize; i++)
	{
		donePrint = donePrint + "|" + std::to_string(doneList.current->getPCB->returnId());
		doneList.current = doneList.current->next;
	}
	doneList.current = doneList.first; // Reset pointer
	cout << donePrint << endl;
	cout << "" << endl;


	//////////////////////////// Print info for active processes

	// Print Headers
	cout << "ID";
	cout << "\tCPU";
	cout << "\t\tIO";
	cout << "\t\t\tPriority" << endl;


	// Print ready
	readySize = sizeofList2(readyList);
	for (int i = 0; i < readySize; i++)
	{
		// Gather process data
		string ID = std::to_string(readyList.current->getPCB->returnId());
		string cpuTotal = std::to_string(readyList.current->getPCB->returnTotalTime());
		string cpuCompleted = std::to_string(readyList.current->getPCB->returnTotalTime() - readyList.current->getPCB->returnTimeLeft());
		string IOTotal = std::to_string(readyList.current->getPCB->returnIO());
		string IOCompleted = std::to_string(readyList.current->getPCB->returnIOLeft());
		string priority = std::to_string(readyList.current->getPCB->returnPriority());

		// Print process data
		cout << ID;
		cout << "\t" << cpuCompleted << "/" << cpuTotal;
		cout << "\t\t" << IOCompleted << "/" << IOTotal;
		cout << "\t\t\t" << priority << endl;

		// Increment
		readyList.current =  readyList.current->next;
	}
	readyList.current = readyList.first; // Reset pointer

	// Print running
	runningSize = sizeofList2(runningList);
	for (int i = 0; i < runningSize; i++)
	{
		// Gather process data
		string ID = std::to_string(runningList.current->getPCB->returnId());
		string cpuTotal = std::to_string(runningList.current->getPCB->returnTotalTime());
		string cpuCompleted = std::to_string(runningList.current->getPCB->returnTotalTime() - runningList.current->getPCB->returnTimeLeft());
		string IOTotal = std::to_string(runningList.current->getPCB->returnIO());
		string IOCompleted = std::to_string(runningList.current->getPCB->returnIOLeft());
		string priority = std::to_string(runningList.current->getPCB->returnPriority());

		// Print process data
		cout << ID;
		cout << "\t" << cpuCompleted << "/" << cpuTotal;
		cout << "\t\t" << IOCompleted << "/" << IOTotal;
		cout << "\t\t\t" << priority << endl;

		// Increment
		runningList.current = runningList.current->next;
	}
	runningList.current = runningList.first; // Reset pointer

	blockedSize = sizeofList2(blockedList);										 // Print blocked
	for (int i = 0; i < blockedSize; i++)
	{
		// Gather process data
		string ID = std::to_string(blockedList.current->getPCB->returnId());
		string cpuTotal = std::to_string(blockedList.current->getPCB->returnTotalTime());
		string cpuCompleted = std::to_string(blockedList.current->getPCB->returnTotalTime() - blockedList.current->getPCB->returnTimeLeft());
		string IOTotal = std::to_string(blockedList.current->getPCB->returnIO());
		string IOCompleted = std::to_string(blockedList.current->getPCB->returnIOLeft());
		string priority = std::to_string(blockedList.current->getPCB->returnPriority());
		
		// Print process data
		cout << ID;
		cout << "\t" << cpuCompleted << "/" << cpuTotal;
		cout << "\t\t" << IOCompleted << "/" << IOTotal;
		cout << "\t\t\t" << priority << endl;

		// Increment
		blockedList.current = blockedList.current->next;
	}
	blockedList.current = blockedList.first; // Reset pointer	



///////////////////////////////Print flags

	// Sleep Flag
	static bool sleep = false;

	// Step
	if (sleep == false)
	{
	
		// check for change in sleep tab
		string temp;
		temp = cin.get();
		if (temp == "\t")
		{
			sleep = true;
			cin.clear();
		}
		
		else if (temp == "\n"){}

		else while(1) {};

		/*
		// wait for enter
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		// finish iteration of main
		*/
	}

	if (sleep == true)
	{
		clock_t wait;
		wait = clock() + 2 * CLOCKS_PER_SEC;
		while (clock() < wait) {};
	}
}

int sizeofList2(listStruct list) {
	int sizecount = 0;
	if (list.current != NULL) {
		sizecount++;
		while (list.current->next != NULL) {
			sizecount++;
			list.current = list.current->next;
		}
	}
	list.current = list.first;
	return sizecount;
}

void runFunc() {
	if (runningList.first == NULL) {
		lowlevel.runProcess();
	}
	else
	{
		runningList.first->getPCB->decTime();
		runningList.first->getPCB->decTSlice();
		if (!(runningList.first->getPCB->returnTimeLeft())) {
			runningToEnd(runningList.first->getPCB);
			lowlevel.runProcess();
		}
		else{
			if (runningList.first->getPCB->returnTimeSlice() == 0) {
				runningToReady(runningList.first->getPCB);
				lowlevel.runProcess();
			}
			else if ((runningList.first->getPCB->returnTimeLeft() + 1) == runningList.first->ioList[runningList.first->getPCB->returnIO() - runningList.first->getPCB->returnIOLeft()][1]) {
				runningList.first->getPCB->countIO(runningList.first->ioList[runningList.first->getPCB->returnIO() - runningList.first->getPCB->returnIOLeft()][0]);
				runningToBlocked(runningList.first->getPCB);
				lowlevel.runProcess();
			}
		}
	}
}