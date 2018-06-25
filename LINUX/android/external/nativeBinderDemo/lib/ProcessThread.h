#ifndef PROCESS_THREAD_H
#define PROCESS_THREAD_H

//#include	"DepthSensor.h"

#include "depthEvaluate.h"

using namespace depth_evaluation;
using namespace std;

namespace android {

class 	ProcessThread : public Thread {
public:
    ProcessThread(DepthSensor * sensor);
    virtual  ~ProcessThread();

public:	
    virtual void onFirstRef();
    virtual status_t  readyToRun();
    virtual bool threadLoop();
    //virtual void     requestExit();
    //void requestLock();


public:	
	status_t start();
	status_t stop();

	void notify();

//private:
	

private:
    sp<ProcessThread> mThread;
	
	mutable Mutex mProcessMutex;
	Condition mProcessCondition;

public:
	DepthSensor * mDepthSensor;
	depth_evaluate * mDepth;
  
};

}


#endif
