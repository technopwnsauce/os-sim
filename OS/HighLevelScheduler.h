#ifndef HIGHLEVELSCHEDULER_H_
#define HIGHLEVELSCHEDULER_H_

#include <iostream>
#include <ctime>
#include "PCB.h"
#include "StateMachine.h"


int gatherPool();

int sizeofList(listStruct);

int gatherPoolIoLevel();

int gatherProcessIoLevel();

bool decideAdmitNewJob();

void admitJob();

void highMain(int);




#endif /* HIGHLEVELSCHEDULER_H_ */
