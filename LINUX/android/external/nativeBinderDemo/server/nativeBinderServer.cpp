#include "../include/common.h"
#include "../lib/INativeService.h"
#include "../lib/NativeService.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>

// 实现server  端
int main() {
	ALOGI("Native Server::+++++++++++++++\r\n");

	// 初始化单例
	sp <ProcessState> proc(ProcessState::self());
	
	// 获取service manager 的binder 引用
	//sp <IServiceManager> sm = defaultServiceManager();
	// 添加服务 ,   注意字符串必须用String16类型
	//sm->addService(String16("service.native"), new BnNativeService());

	NativeService::instantiate();
	
	// 启动线程池INativeService
	ProcessState::self()->startThreadPool();
	// 等待线程结束
	IPCThreadState::self()->joinThreadPool();

	ALOGI("Depth Sensor Server::---------------\r\n");
	
	return 0;
}

