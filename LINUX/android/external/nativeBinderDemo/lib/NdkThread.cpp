#include 	"../include/common.h"

#include	"UsbHid.h"
#include	"NdkThread.h"
#include	"NativeService.h"
#include	"ICallback.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>

using namespace std;

namespace android {  
  
NdkThread::NdkThread(const sp<UsbHid> hid) : Thread(false) {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	mUsbHid = hid;
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
  
NdkThread::~NdkThread() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

bool NdkThread::threadLoop() {

	fd_set readfds;
	
	int i;
	int maxfd,fd;
	int ret;
	ssize_t size;
	
	uint8_t buf[1024];
	
    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	mUsbHid->open_device();
	
	while(!exitPending()){

		size = 0;
		maxfd = 0;
		maxfd = fd = mUsbHid->m_hid_fd;

		FD_ZERO(&readfds);
		
		FD_SET(fd, &readfds);

		ret = select(maxfd + 1, &readfds, NULL, NULL, NULL);
		switch(ret)
		{
			case -1:
				//exit = 1;
				ALOGE("usb hid select failed!(err = %s)\r\n",strerror(errno));
				break;
				
			case 0:
				ALOGW("usb hid select timeout!\r\n");
				break;
		
			default:
				ALOGI("get data event!\r\n");
				if (FD_ISSET(fd, &readfds))
				{
					size = mUsbHid->read_hid_report(buf, sizeof(buf));
					if(size < 0)
					{	
						ALOGE("socket (%d) recv failed!(size = %ld,err = %s)\r\n",i,size,strerror(errno));
						break;
					}
					else if(size == 0)
					{
						ALOGW("socket(%d) disconnect\r\n",i);
						continue;
					}
					else	
					{
						ssize_t len = 0;

						ALOGI("size = %ld\r\n",size);
						for(i=0;i<size;i++)
						{
							ALOGI("buf[%d] = 0x%x\r\n",i,buf[i]);
						}


						for(i=0;i<mUsbHid->mNativeService->mCallback.size();i++)
						{
    						sp<ICallback> c = mUsbHid->mNativeService->mCallback[i];
    						c->notifyCallback(buf,size);  
    					}


    	
						//while(len < size)
						//{
						//	ALOGI("str = %s\r\n",buf + len);
						//	ALOGI("len = %ld\r\n",len);
						//}
					}		
					
				}
				break;
		}
 
		
		#if 0
		if(!mDepthSensor->empty())
		{
			//struct DepthPoint * point = (struct DepthPoint *)mDepthSensor->pop_front();

			//printf("point x = %f\r\n",point->x);
			//printf("point y = %f\r\n",point->y);
			//printf("point z = %f\r\n",poinrt->z);
			
			char * buf;
			buf = mDepthSensor->pop_front();

			for(int i=0;i<16;i++)
			{
				printf("buf[%d] = 0x%d\r\n",i,buf[i]);
			}


			struct DepthPoint * depthRawData = (struct DepthPoint *)buf;

			bool result = mDepth->evaluate_current_depth(depthRawData);
			if(result)
			{
				ALOGI("depth sensor data error!!!\r\n");
				printf("depth sensor data error!!!\r\n");
				exit(0);
			}
			else
			{
				ALOGI("depth sensor a frame ok!!!\r\n");
				printf("depth sensor a frame ok!!!\r\n");
			}

			delete [] buf;
		}
		else
		{
			Mutex::Autolock lock(mProcessMutex);
			mProcessCondition.waitRelative(mProcessMutex,seconds(5));
		}
		#endif
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

    return true;
}  


void NdkThread::notify()
{  	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	Mutex::Autolock lock(mNdkMutex);
	mNdkCondition.signal();
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

void NdkThread::onFirstRef()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

status_t NdkThread::readyToRun()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return NO_ERROR;
}	


status_t NdkThread::start() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    status_t res;
    res = run("NdkThread");
    if (res != OK)
	{
        ALOGE("Unable to start ndk thread:(%s)",strerror(res));
    }
	else
	{
    	ALOGI("start ndk thread OK!");
    }

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return res;
}

status_t NdkThread::stop()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

    requestExitAndWait();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return OK;
}


  
}


