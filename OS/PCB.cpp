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

PCB::PCB(int id, int size, int pLevel, time_t programTime){

	this->identifier = id; //provide the process id
	this->processSize = size; // provides the required size in memory
	this->state = start; //set the state of all new processes to start
	this->priority = pLevel; //set the priority level
	this->programCounter = 0; //temp
	this->contextdata = 0; //temp
	this->io = 0; //temp
	this->ioCounter = 0;//io cycle counter
	this->ioLeft = 0;//io requests left to do
	this->info.timeLeft = programTime; //sets the amount of time the program requires to run
	this->info.timeSlice = TIMESLICE; //sets the value of a timeslice

}

PCB::~PCB(){

}

void PCB::test(){ //test to print out values
	cout << "The id of this process is: " << this->identifier << endl;
}

int PCB::returnId() {
	return this->identifier;
}

void PCB::assignState(ProcessState state){
	this->state = state;
}

ProcessState PCB::returnState(){
	return this->state;
}

void PCB::setIO(int setio) {
	this->io = setio;
	this->ioLeft = setio;
}

bool PCB::checkMem(){
	int count = 0;
	int temp[MEMSIZE] = {0};
	for(int i = 0; i < MEMSIZE; i++){
		if(memory[i] == true) { //checks for free memory
			count++;
			temp[i] = 1; // stores free memory in this temp array
		}
		if(count == this->processSize){ // if there is enough memory
			for(int i = 0; i < MEMSIZE; i++){
				if(temp[i] == 1) {
					memory[i] = false; // sets the memory value to false
					pTable.processID[i] = this->identifier;
				}
			}
			return true;
		}
	}
	return false;
}

void PCB::clearMem(){
	for(int i = 0; i < MEMSIZE; i++) {
		if(pTable.processID[i] == this->identifier){
			pTable.processID[i] = -1;
			memory[i] = true;
		}
	}
}



