#include 	"../include/common.h"

#include	"DepthSensor.h"


#include	"ProcessThread.h"

#include 	"depthEvaluate.h"


// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"FlexDepthSensor"
#include	<cutils/log.h>

using namespace depth_evaluation;
using namespace std;

namespace android {  
  
ProcessThread::ProcessThread(DepthSensor * sensor) : Thread(false) {  
    ALOGI("ProcessThread");
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	mDepthSensor = sensor;

	string file_name = "/data/point_cloud_initial.point";
	mDepth = new depth_evaluate(file_name);			
	
	printf("%s::---------------\r\n",__FUNCTION__);
}
  
ProcessThread::~ProcessThread() {
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("~ProcessThread");
	printf("%s::---------------\r\n",__FUNCTION__);
}  

bool ProcessThread::threadLoop() {
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
    ALOGI("%s::++++++++++", __FUNCTION__);
	
	while(!exitPending()){
		printf("threadLoop--run\r\n");
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
	}
	
	ALOGI("%s::----------", __FUNCTION__);
	printf("%s::---------------\r\n",__FUNCTION__);

    return true;
}  


void ProcessThread::notify() {  
	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
    ALOGI("%s::++++++++++", __FUNCTION__);

	Mutex::Autolock lock(mProcessMutex);
	mProcessCondition.signal();
	
	ALOGI("%s::----------", __FUNCTION__);
}  

void ProcessThread::onFirstRef()
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::++++++++++", __FUNCTION__);
	ALOGI("%s::----------", __FUNCTION__);
	printf("%s::---------------\r\n",__FUNCTION__);
}

status_t ProcessThread::readyToRun()
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::++++++++++", __FUNCTION__);
	ALOGI("%s::----------", __FUNCTION__);
	printf("%s::---------------\r\n",__FUNCTION__);


	return NO_ERROR;
}	


status_t ProcessThread::start() {
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
    ALOGI("%s::++++++++++", __FUNCTION__);
	
    status_t res;
    res = run("ProcessThread");
    if (res != OK)
	{
        ALOGE("%s: Unable to start up Uvc-Probe thread: %s (%d)",
                __FUNCTION__, strerror(-res), res);
    }
	else
	{
    	ALOGI("%s: start process thread OK!", __func__);
    }

	ALOGI("%s::----------", __FUNCTION__);
	printf("%s::---------------\r\n",__FUNCTION__);
	
    return res;
}

status_t ProcessThread::stop()
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

    ALOGI("%s::++++++++++", __FUNCTION__);

    requestExitAndWait();

	ALOGI("%s::----------", __FUNCTION__);
	printf("%s::---------------\r\n",__FUNCTION__);

	return OK;
}


  
}

