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
bool done = 0;
bool statechange = 0;
int idmax = 0;
PageTable pTable;
bool memory[MEMSIZE] = { true };
LowLevelScheduler lowlevel = LowLevelScheduler();
 
using namespace std;

void runFunc();
//void printstuff();

int main(void){ //main function - the OS simulator
	//initialization
	initFile();
	while (!done) {
		processInitializer();//Watch the skipping new problem
		//highlevelscheduler
		
		//run
		lowlevel.decrementIO();
		runFunc();              //timeslice?
		/*if (statechange) {
			//brett's output code
		}*/

		// All under loop indicating change in state machine 
		
	}
	return 0;
}

void printstuff() {
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


	/////////////////////////////Print out of process in each state
	// Print New
	cout << "New" << endl;
	int newSize = sizeof(newList);
	string newPrint = "";
	for (int i = 0; i < newSize; i++)
	{
		string newPrint = newPrint + "," + std::to_string(newList.current->getPCB->returnId());
		newList.current = newList.current->next;
	}
	newList.current = newList.first; // Reset pointer
	cout << newPrint << endl;
	cout << "" << endl;

	// Print Ready
	cout << "Ready" << endl;
	int readySize = sizeof(readyList);
	string readyPrint;
	for (int i = 0; i < readySize; i++)
	{
		string readyPrint = readyPrint + "," + std::to_string(readyList.current->getPCB->returnId());
		readyList.current = readyList.current->next;
	}
	readyList.current = readyList.first; // Reset pointer
	cout << readyPrint << endl;
	cout << "" << endl;

	// Print Running
	cout << "Running" << endl;
	int runningSize = sizeof(runningList);
	string runningPrint;
	for (int i = 0; i < runningSize; i++)
	{
		string runningPrint = runningPrint + "," + std::to_string(runningList.current->getPCB->returnId());
		runningList.current = runningList.current->next;
	}
	runningList.current = runningList.first; // Reset pointer
	cout << runningPrint << endl;
	cout << "" << endl;

	// Print Blocked
	cout << "Blocked" << endl;
	int blockedSize = sizeof(blockedList);
	string blockedPrint;
	for (int i = 0; i < blockedSize; i++)
	{
		string blockedPrint = blockedPrint + "," + std::to_string(blockedList.current->getPCB->returnId());
		blockedList.current = blockedList.current->next;
	}
	blockedList.current = blockedList.first; // Reset pointer
	cout << blockedPrint << endl;
	cout << "" << endl;

	// Print Exit
	cout << "Exit" << endl;
	int doneSize = sizeof(doneList);
	string donePrint;
	for (int i = 0; i < doneSize; i++)
	{
		string donePrint = donePrint + "," + std::to_string(doneList.current->getPCB->returnId());
		doneList.current = doneList.current->next;
	}
	doneList.current = doneList.first; // Reset pointer
	cout << donePrint << endl;
	cout << "" << endl;


	//////////////////////////// Print info for active processes

	// Print Headers
	cout << "ID" << endl;
	cout << "\tCPU" << endl;
	cout << "\t\tIO" << endl;
	cout << "\t\t\tPriority" << endl;


	// Print ready
	for (int i = 0; i < doneSize; i++)
	{
		// Gather process data
		string ID = std::to_string(readyList.current->getPCB->returnId());
		string cpuTotal = std::to_string(readyList.current->getPCB->returnTotalTime());
		string cpuCompleted = std::to_string(readyList.current->getPCB->returnTotalTime() - readyList.current->getPCB->returnTimeLeft());
		string IOTotal = std::to_string(readyList.current->getPCB->returnIO());
		string IOCompleted = std::to_string(readyList.current->getPCB->returnIOLeft());
		string priority = std::to_string(readyList.current->getPCB->returnPriority());

		// Print process data
		cout << ID << endl;
		cout << "\t" + cpuCompleted + "/" + cpuTotal << endl;
		cout << "\t\t" + IOCompleted + "/" + IOTotal << endl;
		cout << "\t\t\t" + priority << endl;
	}
	readyList.current = readyList.first; // Reset pointer

										 // Print running
	for (int i = 0; i < doneSize; i++)
	{
		// Gather process data
		string ID = std::to_string(runningList.current->getPCB->returnId());
		string cpuTotal = std::to_string(runningList.current->getPCB->returnTotalTime());
		string cpuCompleted = std::to_string(runningList.current->getPCB->returnTotalTime() - runningList.current->getPCB->returnTimeLeft());
		string IOTotal = std::to_string(runningList.current->getPCB->returnIO());
		string IOCompleted = std::to_string(runningList.current->getPCB->returnIOLeft());
		string priority = std::to_string(runningList.current->getPCB->returnPriority());

		// Print process data
		cout << ID << endl;
		cout << "\t" + cpuCompleted + "/" + cpuTotal << endl;
		cout << "\t\t" + IOCompleted + "/" + IOTotal << endl;
		cout << "\t\t\t" + priority << endl;
	}
	runningList.current = runningList.first; // Reset pointer

											 // Print blocked
	for (int i = 0; i < doneSize; i++)
	{
		// Gather process data
		string ID = std::to_string(blockedList.current->getPCB->returnId());
		string cpuTotal = std::to_string(blockedList.current->getPCB->returnTotalTime());
		string cpuCompleted = std::to_string(blockedList.current->getPCB->returnTotalTime() - blockedList.current->getPCB->returnTimeLeft());
		string IOTotal = std::to_string(blockedList.current->getPCB->returnIO());
		string IOCompleted = std::to_string(blockedList.current->getPCB->returnIOLeft());
		string priority = std::to_string(blockedList.current->getPCB->returnPriority());

		// Print process data
		cout << ID << endl;
		cout << "\t" + cpuCompleted + "/" + cpuTotal << endl;
		cout << "\t\t" + IOCompleted + "/" + IOTotal << endl;
		cout << "\t\t\t" + priority << endl;
	}
	blockedList.current = blockedList.first; // Reset pointer	



											 ///////////////////////////////Print flags

											 // Step Flag
	bool step = true;

	// Sleep Flag
	bool sleep = false;

	// Step
	if (stateChange == true && sleep == false)
	{
		// clear screen
		system("cls");

		// update
		// wait for enter
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		// finish iteration of main
	}

	// Sleep
	if (stateChange == false && step == true)
	{
		// clear screen
		system("cls");

		//update
		//wait for tab
		cin.ignore(std::numeric_limits<streamsize>::max(), '\t');
		//sleep for 3 seconds
		clock_t wait;
		wait = clock() + 3 * CLOCKS_PER_SEC;
		while (clock() < wait) {};
		//finish main
	}
}

void runFunc() {
	if (runningList.first == NULL) {
		lowlevel.runProcess();
	}
	else
	{
		runningList.first->getPCB->decTime();
		if (!(runningList.first->getPCB->returnTimeLeft())) {
			runningToEnd(runningList.first->getPCB);
			lowlevel.runProcess();
		}
		if ((runningList.first->getPCB->returnTimeLeft() + 1) == runningList.first->ioList[runningList.first->getPCB->returnIO() - runningList.first->getPCB->returnIOLeft()][0]) {
			runningList.first->getPCB->countIO(runningList.first->ioList[runningList.first->getPCB->returnIO() - runningList.first->getPCB->returnIOLeft()][1]);
			runningToBlocked(runningList.first->getPCB);
			lowlevel.runProcess();
		}
	}
	//if(runningList.first) TIME SLICING


}