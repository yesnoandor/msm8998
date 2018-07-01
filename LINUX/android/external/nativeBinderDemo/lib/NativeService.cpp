#include 	"common.h"
#include	"NativeService.h"
#include	"UsbHid.h"

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
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		mDepthSensor = new DepthSensor();
		//mDepthSensor->start();

		// 
		mUsbHid = new UsbHid(this);
		
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}
	
	NativeService::~NativeService()
	{
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}

	void NativeService::instantiate() {
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		defaultServiceManager()->addService(
		String16("service.native"), new NativeService);

		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}

	int NativeService::add(int a, int b) {
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		ALOGI("a = %d\r\n",a);
		ALOGI("b = %d\r\n",b);
				
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return (a+b);
	}


	int NativeService::postRawData(char * buf,int len){
		msg_t * item;
		
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		ALOGI("len = %d\r\n",len);
				
		for(int i=0;i<16;i++)
		{
			printf("buf[%d] = 0x%x\r\n",i,buf[i]);
		}

		item = new msg_t;
		item->buf = (void *)new char[len];
		item->len = len;
		
		memcpy((char *)item->buf,buf,len);

		for(int i=0;i<16;i++)
		{
			printf("item[%d] = 0x%x\r\n",i,((char *)item->buf)[i]);
		}

		
		//mDepthSensor->push_back(item);
		mUsbHid->push_back(item);
		
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return 0;
	}


	int NativeService::setCallback(const sp<ICallback>& callback){
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

		mCallback.push_back(callback);

		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return 0;
	}

	void NativeService::startCallback(){
		int i;
		uint8_t buf[128];
		
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		//sp<ICallback> c = mCallback;
		sp<ICallback> c;
		
		for(int i=0;i<sizeof(buf);i++)
		{
			buf[i] = 3*i + 2;
		}

		ALOGI("mCallback size = %d\r\n",mCallback.size());

		for(i=0;i<mCallback.size();i++)
		{
			c = mCallback[i];
			c->notifyCallback(buf,sizeof(buf));
		}
		
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}

	string NativeService::getVersion(){
		string version = "1.0";
		
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		
		version = string(mVersion);
		
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return version;
	}

	void NativeService::setVersion(String8 version){
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

		ALOGI("version = %s\r\n",version.string());
		
		mVersion = version;
	
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}
}

	

