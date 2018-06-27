#include "../include/common.h"
#include "INativeService.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"ICallback"
#include	<cutils/log.h>

namespace android{  
	//-------------------------------------------
	// 实现ICallback   接口中引用类的各个方法
	// BpCallback 的构造函数
	BpCallback::BpCallback(const sp<IBinder>& impl) :BpInterface<ICallback>(impl) {
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		ALOGI("ICallback:::%s::---------------\r\n",__FUNCTION__);
	}

	// BpCallback 的notifyCallback	方法的实现
	// 并没有实现notifyCallback 的功能
	// 而是跨进程调用Binder  实体对象BnInterface的notifyCallback 方法)
	int BpCallback::notifyCallback(uint8_t *buf,int len) {
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		//Parcel data,reply;

		//data.writeInt32(a);
		//remote()->transact(NOTIFY_CALLBACK_TRANSACTION,data,&reply);


		Parcel data, reply;
		//data.writeInterfaceToken(ICallback::getInterfaceDescriptor());
		data.writeInt32(len);
		data.write(buf, len);
		remote()->transact(NOTIFY_CALLBACK_TRANSACTION,data,&reply);

		ALOGI("%s::---------------\r\n",__FUNCTION__);
				
		return reply.readInt32();
	}
	
	//-------------------------------------------
	// 实现ICallback	接口的方法
	IMPLEMENT_META_INTERFACE(Callback, "android.NativeServer.ICallback");

 
	//-------------------------------------------
	// 实现ICallback  接口实体类的onTransact  方法
	status_t BnCallback::onTransact(uint32_t code, 
										const Parcel& data, 
										Parcel* reply, 
										uint32_t flags){

		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		ALOGI("code = %d\r\n",code);

		switch (code) {
			case NOTIFY_CALLBACK_TRANSACTION:{
				//CHECK_INTERFACE(Itestbinder, data, reply);  
				//reply->writeInt32(notifyCallback((int) data.readInt32()) );

				int32_t size;
                const void *buf;
				
				data.readInt32(&size);
				buf = data.readInplace(size);
				if (buf == NULL) {
					printf("get the error buf!(size = %d)\r\n",size);
					return BAD_VALUE;
				}

				notifyCallback((uint8_t *)buf,size);
				reply->writeInt32(0);
				
				return NO_ERROR;
			}
			break;

			default:{
				return BBinder::onTransact(code, data, reply, flags);
			}
		}
		
		ALOGI("%s::---------------\r\n",__FUNCTION__);
	}  
}  

