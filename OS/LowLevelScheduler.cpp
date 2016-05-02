/*
 * LowLevelScheduler.cpp
 *
 *  Created on: April 27, 2016
 *      Author: Kyle
 */

#include "PCB.h"
#include "LowLevelScheduler.h"
#include "StateMachine.h"

using namespace std;

LowLevelScheduler::LowLevelScheduler() {
    this->currentPriority = 1;
    this->count = 0;
    this->innerCount = 0;
}

LowLevelScheduler::~LowLevelScheduler() {
    
}

void LowLevelScheduler::runProcess() {
        
        if (this->currentPriority == 1 && count < 3) {
            if(getProcess(this->currentPriority) == true){
                count++;
				if (count == 3) {
					this->currentPriority = 2;
				}
            }
            else{
                this->currentPriority = 2;
                count = 0;
            }
        }

		else if(this->currentPriority == 2){
            if(getProcess(this->currentPriority) == true){
                innerCount++;
                if (innerCount == 3) {
                    this->currentPriority = 3;
                }
                else
                    this->currentPriority = 1;
            }
            else{
                this->currentPriority = 3;
            }
        }
		else if (this->currentPriority == 3) {
            if(getProcess(this->currentPriority) == true){
                innerCount = 0;
                this->currentPriority = 1;
            }
            else{
                this->currentPriority = 1;
                innerCount = 0;
            }
        }
		else {
			count = 0;
		}
    
    
}

bool LowLevelScheduler::getProcess(int priority){
    bool priorityFound = false;
	readyList.current = readyList.first;
//	cout << readyList.first << " " << readyList.current << endl;
	if (readyList.first != NULL) {
//		cout << readyList.current->getPCB->returnId() << endl;
		while (readyList.current != NULL) {
			if (readyList.current->getPCB->returnPriority() == priority) {
				readyList.current->getPCB->setTimeSlice(TIMESLICE);
				readyToRunning(readyList.current->getPCB);
				priorityFound = true;
				break;
			}
			readyList.current = readyList.current->next;
		}

/*		if (readyList.current->next == NULL && readyList.current == readyList.first) {
			readyList.current->getPCB->setTimeSlice(TIMESLICE);
			readyToRunning(readyList.current->getPCB);
			priorityFound = true;
			readyList.current = readyList.first;
		} */
		readyList.current = readyList.first;
		return priorityFound;
	}
	else
		return false;
}

void LowLevelScheduler::decrementIO(){
	if (blockedList.first != NULL) {
		if (blockedList.current->getPCB->returnIOCounter()) {
			blockedList.current->getPCB->decrementIOCounter();
		}
		else {
			blockedList.current->getPCB->decIOLeft();
			blockedToReady(blockedList.current->getPCB);
		}
	}
}