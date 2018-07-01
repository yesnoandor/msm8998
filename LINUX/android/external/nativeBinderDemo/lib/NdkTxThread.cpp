#include 	"../include/common.h"

#include	"UsbHid.h"
#include	"NdkTxThread.h"
#include	"NativeService.h"
//#include	"ICallback.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>

using namespace std;

namespace android {  
  
NdkTxThread::NdkTxThread(const sp<UsbHid> hid) : Thread(false) {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	mUsbHid = hid;
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
  
NdkTxThread::~NdkTxThread() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

bool NdkTxThread::threadLoop() {	
	int i;

	int ret;
	ssize_t size;
	
	//uint8_t buf[1024];
	
    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	//mUsbHid->open_device();
	
	while(!exitPending()){
		if(!mUsbHid->empty())
		{
			//struct DepthPoint * point = (struct DepthPoint *)mDepthSensor->pop_front();

			//printf("point x = %f\r\n",point->x);
			//printf("point y = %f\r\n",point->y);
			//printf("point z = %f\r\n",poinrt->z);
			
			msg_t * item;

			item = mUsbHid->pop_front();
			mUsbHid->write_hid_report((uint8_t *)item->buf,item->len);

			delete [] item->buf;
			delete [] item;
		}
		else
		{
			Mutex::Autolock lock(mNdkTxMutex);
			mNdkTxCondition.waitRelative(mNdkTxMutex,seconds(5));
		}

	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

    return true;
}  


void NdkTxThread::notify()
{  	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	Mutex::Autolock lock(mNdkTxMutex);
	mNdkTxCondition.signal();
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

void NdkTxThread::onFirstRef()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

status_t NdkTxThread::readyToRun()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return NO_ERROR;
}	


status_t NdkTxThread::start() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    status_t res;
    res = run("NdkTxThread");
    if (res != OK)
	{
        ALOGE("Unable to start ndk tx thread:(%s)",strerror(res));
    }
	else
	{
    	ALOGI("start ndk tx thread OK!");
    }

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return res;
}

status_t NdkTxThread::stop()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

    requestExitAndWait();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return OK;
}


  
}


