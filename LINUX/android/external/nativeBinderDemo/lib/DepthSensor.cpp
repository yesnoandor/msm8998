

#include 	"../include/common.h"

#include	"DepthSensor.h"
#include	"ProcessThread.h"





namespace android {

DepthSensor::DepthSensor(void)
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	mProcessThread = new ProcessThread(this);
	mProcessThread->start();

	printf("%s::---------------\r\n",__FUNCTION__);
}

DepthSensor::~DepthSensor()
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	printf("%s::---------------\r\n",__FUNCTION__);
}


void DepthSensor::push_back(char * item)
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	mDepthSensorQueue.push_back(item);
	mProcessThread->notify();

	printf("%s::---------------\r\n",__FUNCTION__);
}

char * DepthSensor::pop_front()
{
	char * item;
	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	item = mDepthSensorQueue.front();
	mDepthSensorQueue.pop_front();

	printf("%s::---------------\r\n",__FUNCTION__);

	return item;
}


bool DepthSensor::empty()
{
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	printf("%s::---------------\r\n",__FUNCTION__);

	return mDepthSensorQueue.empty();
}


}; // namespace android

