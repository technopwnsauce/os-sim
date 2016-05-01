/*
 * PCB.h
 *
 *  Created on: Mar 22, 2016
 *      Author: kylearchuleta
 */

#ifndef PCB_H_
#define PCB_H_
#include <iostream>
#include <ctime>

#define TIMESLICE 100 //temporary value for timeslice
#define MEMSIZE 16 // The OS runs on a 16 MB RAM

//int ioTable = 

struct AccountingInfo{
	time_t timeLeft; //time used
	time_t timeSlice; //time limits
	//int account number; //account number  
};

struct PageTable { 	//the page table holds the location in memory as well as the process id number
	int location[MEMSIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int processID[MEMSIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; //sets to a nonsense value until assigned
};

extern PageTable pTable;
extern bool memory[];

//global instance of the page table
//PageTable pTable;

//global memory
//bool memory[MEMSIZE] = {true}; //memory is either free (true) or taken (false)

enum ProcessState {start,ready,blocked,running,endstate};//state variables (global variable)

class PCB {
private:
	int identifier; //Unique identifier for each process
	int processSize; //how much memory is required to run
	ProcessState state; //State of the process
	int priority; //Priority level relative to other processes
	int totalTime; //Address of the next instruction in the program to be executed
	int contextdata; //data that are present in registers in the processor while its executing
	int io;
	int ioLeft; //work on, includes outstanding IO requires, devices, list of files in use, etc
	int ioCounter;
	AccountingInfo info;
public:
	PCB(int, int, int, time_t);
	~PCB();
	void test(); //test method to print info
	void decTime();//decrements time left
	void decrementIOCounter();
	void assignState(ProcessState state); //method to assign a state to a process
	ProcessState returnState(); //method to return the current state of a process
	int returnTotalTime();
	int returnId();//method to return the process's ID
    int returnPriority();//method to reutrn the process's priority level
	int returnIOLeft();
	int returnTimeLeft();
	int returnIO();
	int returnIOCounter();
	void setIO(int setio);
	void setID(int id);
	void countIO(int);
	bool checkMem();//method to see if there is enough memory available
	void clearMem();//method to free memory
	bool checkMemLeft();
};

#endif /* PCB_H_ */
