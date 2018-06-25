/*
* 
*
*/
#include "../include/common.h"
#include "ICallback.h"

#ifndef INATIVE_SERVICE_H
#define INATIVE_SERVICE_H


using namespace android;
using namespace std;


namespace android
{
	// 申明service  接口INativeService
	class INativeService : public IInterface
	{			
		public:
		    // 申明了一些代码，包括
		    // 添加了字段descriptor，
		    // 添加了两个成员函数asInterface，getInterfaceDescriptor
			// 添加了构造器和析构器
			DECLARE_META_INTERFACE(NativeService);
	        
	        // 该服务对外提供的操作接口
			virtual int add(int a,int b)=0;		// 加法运算
			virtual int postRawData(char * buf,int length) = 0;			// 传输原始数据

			virtual int setCallback(const sp<ICallback>& callback) = 0;		// 设置回调
			virtual void startCallback() = 0;								// 启动回调

			virtual string getVersion() = 0;
			virtual void setVersion(String8 version) = 0;
	};


	// 声明枚举INativeService	接口的所有方法
	enum{ 
		ADD_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
		POST_RAW_DATA_TRANSACTION,
		SET_CALLBACK_TRANSACTION,
		START_CALLBACK_TRANSACTION,
		GET_VERSION_TRANSACTION,
		SET_VERSION_TRANSACTION,
	};
			

	// 声明binder  服务的实体类BnNativeService, 继承BnInterface
	class BnNativeService: public BnInterface<INativeService> {
		public:
			virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,uint32_t flags = 0);
	};


	// 声明binder  服务的引用类BpNativeService, 继承BpInterface
	class BpNativeService: public BpInterface<INativeService> {
		public:
			BpNativeService(const sp<IBinder>& impl);

			virtual int add(int a,int b);
			virtual int postRawData(char * buf,int len);
			virtual int setCallback(const sp<ICallback>& callback);
			virtual void startCallback();	
			virtual string getVersion();
			virtual void setVersion(String8 version);
	};
}

#endif
