#include "../include/common.h"
#include "../lib/INativeService.h"
#include "../lib/ICallback.h"
#include "../lib/Callback.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeClient"
#include	<cutils/log.h>




void onMessage(int msg_id, void * msg_buf, int msg_len)
{
	int i;
	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	ALOGI("msg_id = %d\r\n",msg_id);

	for(i=0;i<msg_len;i++)
	{
		ALOGI("msg[i] = 0x%x\r\n",i,((uint8_t *)msg_buf)[i]);	
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}



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
	c->registerOnMessage(onMessage);
	int a = cs->setCallback(c);
	
	
	//sp<Callback> c2 = new Callback();
	//c2->registerOnMessage(onMessage);
	//a = cs->setCallback(c2);

	
	// 通过binder 引用调用add 方法
	cs->add(5,8);
	
	cs->setVersion(String8("3.0"));
	
	cs->getVersion();


	// 通过binder 引用调用startCallback  方法
	//cs->startCallback();


	// 通过binder 引用调用setDepthSensorRawData  方法
	memset(buf,0x00,sizeof(buf));
	for(int i=0;i<sizeof(buf);i++)
	{
		buf[i] = 3*i+2;
	}
	//cs->postRawData(buf,sizeof(buf));
	
	do{
		sleep(20);
		ALOGI("send...\r\n");

		cs->postRawData(buf,32);
	}while(1);

	return 0;
}

