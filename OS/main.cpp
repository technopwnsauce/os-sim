/*
 * main.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: kylearchuleta
 */

#include <iostream>
#include <ctime>
#include "PCB.h"
#include "StateMachine.h"
#include "StateMachineTest.h"
using namespace std;

int main(void){ //main function - the OS simulator

	//some test "processes to see if the PCB works.

	ProcessState state;

	PCB process1(0,1,1000);
	PCB process2(1,2,600);
	PCB process3(2,2,400);

	process1.test();
	process2.test();
	process3.test();

	//correctly prints out the state of process1 (start, 0)
	state = process1.returnState();
	cout << state << endl;
	//assign state to 3
	state = running;
	process1.assignState(state);
	//assign state back to 0
	state = start;
	//return state of process (3)
	state = process1.returnState();
	cout << state << endl;
	while (1);
	return 0;
}

