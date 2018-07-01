#include	"UsbHid.h"

using namespace std;

namespace android {

class 	NdkTxThread : public Thread {
public:
    NdkTxThread(const sp<UsbHid> hid);
    virtual  ~NdkTxThread();

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
    sp<NdkTxThread> mNdkTxThread;
	
	mutable Mutex mNdkTxMutex;
	Condition mNdkTxCondition;

public:
	sp<UsbHid> mUsbHid;

//public:
	//DepthSensor * mDepthSensor;
	//depth_evaluate * mDepth;
  
};

}



