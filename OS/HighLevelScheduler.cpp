// Issues
	// Need to check that process is entirely in memory before moving from new to ready

// Primary Idea: Call HighLevelScheduler on a process when it enters the new state to determine if it should be admitted currently

#include "HighLevelScheduler.h"
#include "StateMachine.h"
#include "PCB.h"
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

/*extern listStruct newList;
extern listStruct readyList;
extern listStruct runningList;
extern listStruct blockedList;
extern listStruct doneList;*/

// Gets current pool count
int gatherPool()
{
	// Grab current processes in each state
	/*extern listStruct newList;
	extern listStruct readyList;
	extern listStruct runningList;
	extern listStruct blockedList;
	extern listStruct doneList;*/

	// Calculate the total number of processes in the pool (those in ready, running, blocked)
	poolCount = sizeof(readyList) + sizeof(runningList) + sizeof(blockedList);
	return poolCount;
}

// Gathers current pool I/O level
int gatherPoolIoLevel()
{
	// Tally the total number of I/O requests in ready
	int readySize = sizeof(readyList);
	int readyTotal = 0;
	for(int i=0; i<readySize; i++)
	{
		readyTotal = readyTotal + readyList.current->getPCB->returnIOLeft();
		readyList.current = readyList.current->next;
	}
	readyList.current = readyList.first; // Reset pointer

	// Tally the total number of I/O requests in running
	int runningSize = sizeof(runningList);
	int runningTotal = 0;
	for(int i=0; i<runningSize; i++)
	{
		runningTotal = runningTotal + runningList.current->getPCB->returnIOLeft();
		runningList.current = runningList.current->next;
	}
	runningList.current = runningList.first; // Reset pointer

	// Tally the total number of IO requests in blocked
	int blockedSize = sizeof(blockedList);
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
	poolIoLevel = floor(poolTotal/poolMax) * 100;
	return poolIoLevel;
}

// Gathers considered process I/O level
int gatherProcessIoLevel()
{
	// Match PID with PCB ID, then pull number of I/O request
	int rawIo;
	for (int i=0; i<sizeof(newList); i++)
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
	}

	if (poolCount < 50)
	{
		int tempPoolIoLevel = 0;
		tempPoolIoLevel = floor(((poolIoLevel + processIoLevel) / (poolCount + 1)));
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
    bool memory;
    for (int i=0; i<sizeof(newList); i++)
    {
        if(PID == newList.current->getPCB->returnId())
        {
            memory = newList.current->getPCB->checkMemLeft();
            break;
        }
        
        else if(PID != newList.current->getPCB->returnId())
        {
            newList.current = newList.current->next;
        }
    }
    newList.current = newList.first; // Reset pointer
    if(memory == false)
    {
        newJobAdmissionStatus = false;
    }
    
	return newJobAdmissionStatus;
}

// Admits a new job when applicable
void admitJob()
{
	if (newJobAdmissionStatus == true)
	{
		for (int i=0; i<sizeof(newList); i++)
		{
			if(PID == newList.current->getPCB->returnId())
			{
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
}
