/*
 * HighLevelScheduler.h
 *
 *  Created on: Mar 22, 2016
 *      Author: Brett
 */

#ifndef HIGHLEVELSCHEDULER_H_
#define HIGHLEVELSCHEDULER_H_

#include "PCB.h"
#include "math.h"

class HighLevelScheduler
{
private:
	bool newJobAdmissionStatus; // Indicates whether a new job will be admitted? (T=Admit, F=No Admit)
	std::string entityStatus; // Indicates whether entity is (Job/Process/Terminated)
	// used to decide process admission
	int processPriority; // Process priority
	int expectedExecutionTime;// Expected execution time
	int processIoLevel; // Integer rating of process's level of I/O utilization
	int poolIoLevel; // Averaged integer rating of entire pool's level of I/O utilization
	int poolIoLevels[100]; //Stores IO rating of each of the potential 100 processes in the pool
	int poolCount; // Number of processes in the pool
public:
	HighLevelScheduler();
	virtual ~HighLevelScheduler();
};

#endif /* HIGHLEVELSCHEDULER_H_ */
