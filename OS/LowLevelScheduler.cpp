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
    
    
}

bool LowLevelScheduler::getProcess(int priority){
    bool priorityFound = false;
	if (readyList.current != NULL) {
		while (readyList.current->next != NULL) {
			if (readyList.current->getPCB->returnPriority() == priority) {
				readyToRunning(readyList.current->getPCB);
				priorityFound = true;
				break;
			}
			readyList.current = readyList.current->next;
		}
		readyList.current = readyList.first;
		return priorityFound;
	}
	else
		return 1;
}

void LowLevelScheduler::decrementIO(){
	if (blockedList.first != NULL) {
		if (blockedList.current->getPCB->returnIOCounter())
			blockedList.current->getPCB->decrementIOCounter();
	}
}