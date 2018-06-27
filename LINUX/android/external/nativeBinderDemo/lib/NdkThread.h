#include	"UsbHid.h"

using namespace std;

namespace android {

class 	NdkThread : public Thread {
public:
    NdkThread(const sp<UsbHid> hid);
    virtual  ~NdkThread();

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
    sp<NdkThread> mNdkThread;
	
	mutable Mutex mNdkMutex;
	Condition mNdkCondition;

public:
	sp<UsbHid> mUsbHid;

//public:
	//DepthSensor * mDepthSensor;
	//depth_evaluate * mDepth;
  
};

}



