/*
* LowLevelScheduler.h
*
*  Created on: April 27, 2016
*      Author: Kyle
*/

#ifndef HIGHLEVELSCHEDULER_H_
#define HIGHLEVELSCHEDULER_H_

//#include "PCB.h"

class LowLevelScheduler {
    
private:
    int currentPriority;
    int count;
    int innerCount;
    
public:
    
    LowLevelScheduler(); //constructor
    ~LowLevelScheduler(); //deletor
    void runProcess(void); //decides which process to run
    bool getProcess(int);
    void decrementIO(void);
    
    
};

#endif // LOWLEVELSCHEDULER_H_ 