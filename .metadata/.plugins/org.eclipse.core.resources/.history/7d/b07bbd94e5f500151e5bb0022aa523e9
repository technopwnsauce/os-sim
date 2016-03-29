/*
 * PCB.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: kylearchuleta
 */

#include <iostream>
#include <ctime>
#include "PCB.h"

using namespace std;

PCB::PCB(int id, int pLevel, time_t programTime){

	this->identifier = id; //provide the process id
	this->state = start; //set the state of all new processes to start
	this->priority = pLevel; //set the priority level
	this->programCounter = 0; //temp
	this->memoryPointer = 0; //temp
	this->contextdata = 0; //temp
	this->io = 0; //temp
	this->info.timeLeft = programTime; //sets the amount of time the program requires to run
	this->info.timeSlice = TIMESLICE; //sets the value of a timeslice

}

PCB::~PCB(){

}

void PCB::test(){ //test to print out values
	cout << "The id of this process is: " << this->identifier << endl;
}




