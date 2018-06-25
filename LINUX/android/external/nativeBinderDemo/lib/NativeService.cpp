#include 	"../include/common.h"
#include	"NativeService.h"

#include	"depthEvaluate.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>

using namespace depth_evaluation;


namespace android {
	NativeService::NativeService() :
		BnNativeService()
	{
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);

		mDepthSensor = new DepthSensor();
		//mDepthSensor->start();
		
		printf("%s::---------------\r\n",__FUNCTION__);
		ALOGI("%s::---------------\r\n",__FUNCTION__);
	}
	
	NativeService::~NativeService()
	{
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);

		printf("%s::---------------\r\n",__FUNCTION__);

	}

	void NativeService::instantiate() {
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);
		
		defaultServiceManager()->addService(
		String16("service.native"), new NativeService);

		printf("%s::---------------\r\n",__FUNCTION__);
	}

	int NativeService::add(int a, int b) {
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);

		printf("a = %d\r\n",a);
		printf("b = %d\r\n",b);
				
		printf("%s::---------------\r\n",__FUNCTION__);

		return (a+b);
	}


	int NativeService::postRawData(char * buf,int len){
		char * item;
		
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);

		printf("len = %d\r\n",len);
				
		for(int i=0;i<16;i++)
		{
			printf("buf[%d] = 0x%x\r\n",i,buf[i]);
		}

		item = new char[len];

		memcpy((char *)item,buf,len);

		for(int i=0;i<16;i++)
		{
			printf("item[%d] = 0x%x\r\n",i,item[i]);
		}

		mDepthSensor->push_back(item);
		
		printf("%s::---------------\r\n",__FUNCTION__);

		return 0;
	}


	int NativeService::setCallback(const sp<ICallback>& callback){
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

		mCallback = callback;

		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return 0;
	}

	void NativeService::startCallback(){
		int i;
		uint8_t buf[128];
		
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		printf("start callback test...\r\n");

		sp<ICallback> c = mCallback;

		for(int i=0;i<sizeof(buf);i++)
		{
			buf[i] = 3*i + 2;
		}
    	c->notifyCallback(buf,sizeof(buf));  

		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}

	string NativeService::getVersion(){
		string version = "1.0";
		
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		

		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		version = string(mVersion);
		return version;
	}

	void NativeService::setVersion(String8 version){
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

		printf("version = %s\r\n",version.string());
		ALOGI("version = %s\r\n",version.string());
		
		mVersion = version;
	
		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	}
}

	

