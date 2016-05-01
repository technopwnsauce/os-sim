#ifndef HIGHLEVELSCHEDULER_H_
#define HIGHLEVELSCHEDULER_H_

#include <iostream>
#include <ctime>

int gatherPool();

int gatherPoolIoLevel();

int gatherProcessIoLevel();

bool decideAdmitNewJob();

void admitJob();

void highMain(int processID);




#endif /* HIGHLEVELSCHEDULER_H_ */
