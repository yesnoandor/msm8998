#include "../include/common.h"
#include "../lib/INativeService.h"
#include "../lib/ICallback.h"
#include "../lib/Callback.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>

// 实现client   
int main() {
	char buf[128];			// 128*1024

	ALOGI("Native Client::+++++++++++++++\r\n");
	
	// 获取service manager 引用
	sp <IServiceManager> sm = defaultServiceManager();
	// 获取depth sensor service的binder  接口对象
	sp <IBinder> binder = sm->getService(String16("service.native"));
	// 转为sp <IDepthSensorService>
	sp <INativeService> cs = interface_cast <INativeService> (binder);

	ProcessState::self()->startThreadPool();
	
	sp<Callback> c = new Callback();
	int a = cs->setCallback(c);  

	sp<Callback> c2 = new Callback();
	a = cs->setCallback(c2);  
	
	// 通过binder 引用调用add 方法
	cs->add(5,8);
	
	// 通过binder 引用调用setDepthSensorRawData  方法
	memset(buf,0x00,sizeof(buf));
	for(int i=0;i<sizeof(buf);i++)
	{
		buf[i] = 3*i+1;
	}
	cs->postRawData(buf,sizeof(buf));


	cs->setVersion(String8("3.0"));
	
	cs->getVersion();


	// 通过binder 引用调用startCallback  方法
	//cs->startCallback();

	
	do{
		sleep(20);
		ALOGI("wait...\r\n");
	}while(1);

	return 0;
}

