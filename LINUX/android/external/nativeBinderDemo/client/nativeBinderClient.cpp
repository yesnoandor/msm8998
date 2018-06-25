#include "../include/common.h"
#include "../lib/INativeService.h"
#include "../lib/ICallback.h"
#include "../lib/Callback.h"



// ʵ��client   
int main() {
	char buf[128];			// 128*1024
	
	// ��ȡservice manager ����
	sp <IServiceManager> sm = defaultServiceManager();
	// ��ȡdepth sensor service��binder  �ӿڶ���
	sp <IBinder> binder = sm->getService(String16("service.native"));
	// תΪsp <IDepthSensorService>
	sp <INativeService> cs = interface_cast <INativeService> (binder);

	sp<Callback> c = new Callback();
	ProcessState::self()->startThreadPool();
	int a = cs->setCallback(c);  

	
	// ͨ��binder ���õ���add ����
	cs->add(5,8);
	
	// ͨ��binder ���õ���setDepthSensorRawData  ����
	memset(buf,0x00,sizeof(buf));
	for(int i=0;i<sizeof(buf);i++)
	{
		buf[i] = 3*i+1;
	}
	cs->postRawData(buf,sizeof(buf));

	// ͨ��binder ���õ���startCallback  ����
	cs->startCallback();

	cs->setVersion(String8("3.0"));
	
	cs->getVersion();
	
	return 0;
}

