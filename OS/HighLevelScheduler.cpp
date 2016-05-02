// Issues
	// Need to check that process is entirely in memory before moving from new to ready

// Primary Idea: Call HighLevelScheduler on a process when it enters the new state to determine if it should be admitted currently

#include "HighLevelScheduler.h"
#include "StateMachine.h"
#include<fstream>
#include<istream>
#include<string>
#include <ctime>
#include <iostream>

using namespace std;

bool newJobAdmissionStatus; // Indicates whether new process will be admitted
int processIoLevel; // Integer rating of process's level of I/O utilization (0-100)
int poolIoLevel; // Averaged integer rating of entire pool's level of I/O utilization (0-100)
int poolCount; // Number of processes in the pool (i.e. those in ready,running,blocked)
int PID; // ID of process being considered for admission

// Gets current pool count
int gatherPool()
{

	// Calculate the total number of processes in the pool (those in ready, running, blocked)
	poolCount = sizeofList(readyList) + sizeofList(runningList) + sizeofList(blockedList);
	return poolCount;
}

int sizeofList(listStruct list) {
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

// Gathers current pool I/O level
int gatherPoolIoLevel()
{
	// Tally the total number of I/O requests in ready
	int readySize = sizeofList(readyList);
	int readyTotal = 0;

	for (int i = 0; i < readySize; i++)
	{
		readyTotal = readyTotal + readyList.current->getPCB->returnIOLeft();
		readyList.current = readyList.current->next;
	}
	readyList.current = readyList.first; // Reset pointer

	// Tally the total number of I/O requests in running
	int runningSize = sizeofList(runningList);
	int runningTotal = 0;
	for(int i=0; i<runningSize; i++)
	{
		runningTotal = runningTotal + runningList.current->getPCB->returnIOLeft();
		runningList.current = runningList.current->next;
	}
	runningList.current = runningList.first; // Reset pointer

	// Tally the total number of IO requests in blocked
	int blockedSize = sizeofList(blockedList);
	int blockedTotal = 0;
	for(int i=0; i<blockedSize; i++)
	{
		blockedTotal = blockedTotal + blockedList.current->getPCB->returnIOLeft();
		blockedList.current = blockedList.current->next;
	}
	blockedList.current = blockedList.first; // Reset pointer

	// Calculate poolIoLevel
	int poolTotal = readyTotal + runningTotal + blockedTotal;
	int poolMax = (readySize + runningSize + blockedSize) * 5;
	if (poolMax != 0)
	{
		poolIoLevel = floor(poolTotal / poolMax) * 100;

	}
	else{
		poolIoLevel = 0;
	}
	return poolIoLevel;
}

// Gathers considered process I/O level
int gatherProcessIoLevel()
{
	// Match PID with PCB ID, then pull number of I/O request
	int rawIo = 0;
	for (int i=0; i<sizeofList(newList); i++)
	{
		if(PID == newList.current->getPCB->returnId())
		{
			rawIo = newList.current->getPCB->returnIOLeft();
			break;
		}

		else if(PID != newList.current->getPCB->returnId())
		{
			newList.current = newList.current->next;
		}
	}
	newList.current = newList.first; // Reset pointer

	// Calculate process I/O Level
	processIoLevel = rawIo * 20;
	return processIoLevel;
}

// Decides whether or not to admit a new job
bool decideAdmitNewJob()
{
	if (poolCount >= 50)
	{
		newJobAdmissionStatus = false;
		// cout << "newJobAdmissionStatus: " + std::to_string(newJobAdmissionStatus) + "\n"; // DEBUG
	}

	if (poolCount < 50)
	{
		int tempPoolIoLevel = 0;
		tempPoolIoLevel = floor(((poolIoLevel + processIoLevel) / (poolCount + 1) / ((poolCount+1)*100)));
		/*cout << "pool io level is " + std::to_string(poolIoLevel) + "\n";
		cout << "process io level is:" + std::to_string(processIoLevel) + "\n";
		cout << "pool count is: " + std::to_string(poolCount) + "\n";
		cout << "temp pool io level:" + std::to_string(tempPoolIoLevel) + "\n"; */
		if (tempPoolIoLevel < 50)
		{
			newJobAdmissionStatus = true;
		}
		else
		{
			newJobAdmissionStatus = false;
		}
	}
    // If there is not enough memory for the process then set newJobAdmissionStatus = false
    // Match PID with PCB ID, then pull number of I/O request
    bool mem = false;
    for (int i=0; i<sizeofList(newList); i++)
    {
        if(PID == newList.current->getPCB->returnId())
        {
            mem = newList.current->getPCB->checkMemLeft();
            break;
        }
        
        else if(PID != newList.current->getPCB->returnId())
        {
            newList.current = newList.current->next;
        }
    }
    newList.current = newList.first; // Reset pointer
    if(mem == false)
    {
        newJobAdmissionStatus = false;
    }
	else newJobAdmissionStatus = true;
    
	return newJobAdmissionStatus;
}

// Admits a new job when applicable
void admitJob()
{
	//cout << "admission status when admitting job is: " + std::to_string(newJobAdmissionStatus) + "\n";
	if (newJobAdmissionStatus == true)
	{
		for (int i=0; i<sizeofList(newList); i++)
		{
			if(PID == newList.current->getPCB->returnId())
			{
				newList.current->getPCB->checkMem();
			//	cout << "Hello, i am " << newList.current->getPCB->returnId() << endl;
			//	for (int i = 0; i < 1000000000; i++) {};
				newToReady(newList.current->getPCB);
				break;
			}

			else if(PID != newList.current->getPCB->returnId())
			{
				newList.current = newList.current->next;
			}
		}
	}
	newList.current = newList.first; // Reset pointer
}

// "main" function of the HighLevelScheduler, takes a PID and calls all necessary functions to decide whether or not to admit a process
void highMain(int processID)
{
	PID = processID;
	gatherPool();
	gatherPoolIoLevel();
	gatherProcessIoLevel();
	decideAdmitNewJob();
	admitJob();

	// DEBUGS
	/*cout << "Admission Status: " + std::to_string(newJobAdmissionStatus) + "\n";
	cout << "processIoLevel: " + std::to_string(processIoLevel) + "\n";
	cout << "poolIoLevel: " + std::to_string(poolIoLevel) + "\n";
	cout << "poolCount: " + std::to_string(poolCount) + "\n";
	cout << "PID: " + std::to_string(PID) + "\n";*/
}
