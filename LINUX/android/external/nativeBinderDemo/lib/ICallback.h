/*
* 
*
*/



#ifndef ICALLBACK_H    
#define ICALLBACK_H

using namespace android;

namespace android{
	// 申明callback  接口ICallback
	class ICallback : public IInterface{
		public:
			// 申明了一些代码，包括
		    // 添加了字段descriptor，
		    // 添加了两个成员函数asInterface，getInterfaceDescriptor
			// 添加了构造器和析构器
			DECLARE_META_INTERFACE(Callback);

			// 该接口对外提供的操作接口
			virtual int notifyCallback(uint8_t *buf,int len) = 0;
	};

	// 声明枚举ICallback	接口的所有方法
	enum {
		NOTIFY_CALLBACK_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
	};

	// 声明callback  的实体类BnCallback, 继承BnInterface
	class BnCallback : public BnInterface<ICallback>{
		public:
			virtual status_t    onTransact( uint32_t code,  
                                    const Parcel& data,  
                                    Parcel* reply,  
                                    uint32_t flags = 0);
	};

	// 声明callback  接口的引用类BpCallback, 继承BpInterface
	class BpCallback: public BpInterface<ICallback> {
		public:
			BpCallback(const sp<IBinder>& impl);
			
			virtual int notifyCallback(uint8_t *buf,int len);
	};
}

#endif 

