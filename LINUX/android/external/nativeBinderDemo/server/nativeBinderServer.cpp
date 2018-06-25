#include "../include/common.h"
#include "../lib/INativeService.h"
#include "../lib/NativeService.h"


// ʵ��server  ��
int main() {
	ALOGI("Depth Sensor Server::+++++++++++++++\r\n");

	// ��ʼ������
	sp <ProcessState> proc(ProcessState::self());
	
	// ��ȡservice manager ��binder ����
	//sp <IServiceManager> sm = defaultServiceManager();
	// ��ӷ��� ,   ע���ַ���������String16����
	//sm->addService(String16("service.native"), new BnNativeService());

	NativeService::instantiate();
	
	// �����̳߳�INativeService
	ProcessState::self()->startThreadPool();
	// �ȴ��߳̽���
	IPCThreadState::self()->joinThreadPool();

	ALOGI("Depth Sensor Server::---------------\r\n");
	
	return 0;
}

