#include "../include/common.h"
#include "INativeService.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>


namespace android
{
	//-------------------------------------------
	// 实现BpNativeService  中的各个方法
	// BpNativeService 的构造函数
	BpNativeService::BpNativeService(const sp<IBinder>& impl) :BpInterface<INativeService>(impl) {
	
	}
	
	// BpNativeService 的add	方法的实现
	// 并没有实现add 的功能
	// 而是跨进程调用Binder  实体对象BnInterface的add 方法)
	int BpNativeService::add(int a,int b) {
		int c = 0;
				
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);
	
		printf("a = %d\r\n", a);
		printf("b = %d\r\n", b);
				
		Parcel data, reply;
		data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
		data.writeInt32(a);
		data.writeInt32(b);
		remote()->transact(ADD_TRANSACTION, data, &reply);
	
		c = reply.readInt32();
		printf("val = %d\r\n", c);
		
		printf("%s::---------------\r\n",__FUNCTION__);
	
		return c;
	}

	// BpNativeService 的postRawData  方法的实现
	int BpNativeService::postRawData(char * buf,int len){
		
		printf("%s::+++++++++++++++\r\n",__FUNCTION__);
			 
		printf("post raw data...\r\n");
			
		printf("len = %d\r\n",len);

		Parcel data, reply;
		data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
		data.writeInt32(len);
		data.write(buf, len);
				   
		remote()->transact(POST_RAW_DATA_TRANSACTION, data, &reply);
			
		printf("get result %d\r\n", reply.readInt32());
			
		printf("%s::---------------\r\n",__FUNCTION__);

		return 0;
	}


	// BpNativeService 的setCallback  方法的实现
	int BpNativeService::setCallback(const sp<ICallback>& callback){  
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
			
		Parcel data, reply;

		data.writeStrongBinder(IInterface::asBinder(callback));
		remote()->transact(SET_CALLBACK_TRANSACTION, data, &reply);

		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return reply.readInt32();
	} 

	// BpNativeService 的startCallback  方法的实现
	void BpNativeService::startCallback() {
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
	 
		Parcel data, reply;
		data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
		remote()->transact(START_CALLBACK_TRANSACTION, data, &reply);
	
		printf("get result %d\r\n",reply.readInt32());
	
		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}

	// BpNativeService 的startCallback  方法的实现
	string BpNativeService::getVersion() {
		string version;
		
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
	 
		Parcel data, reply;
		data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
		remote()->transact(GET_VERSION_TRANSACTION, data, &reply);

		version = reply.readCString();
		
		printf("get version %s\r\n",version.c_str());
	
		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return version;
	}

	void BpNativeService::setVersion(String8 version){
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

	 	printf("version123 = %s\r\n",version.string());
		ALOGI("version123 = %s\r\n",version.string());

		Parcel data, reply;
		data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
		data.writeString8(version);
		remote()->transact(SET_VERSION_TRANSACTION, data, &reply);
	

		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}

	//-------------------------------------------
	// 实现INativeService   接口的方法
	IMPLEMENT_META_INTERFACE(NativeService, "android.NativeServer.INativeService");

	
	
	
	//-------------------------------------------
	// 实现INativeService  实体类的onTransact  方法
	status_t BnNativeService::onTransact(uint_t code, const Parcel& data,
		Parcel* reply, uint32_t flags) {
		switch (code) {
			case ADD_TRANSACTION:{
					printf("got the add request\r\n");
					CHECK_INTERFACE(INative, data, reply);
					
					int a = data.readInt32();
					int b = data.readInt32();

					printf("a = %d\r\n",a);
					printf("b = %d\r\n",b);
				
					int c = add(a,b);
					reply->writeInt32(c);
					
					return NO_ERROR;
				}
				break;

			case POST_RAW_DATA_TRANSACTION:{
					printf("got the raw data!\n");
					CHECK_INTERFACE(INative, data, reply);

					int32_t size;
                	const void *buf;
				
					data.readInt32(&size);
					buf = data.readInplace(size);
					if (buf == NULL) {
						printf("get the error buf!(size = %d)\r\n",size);
						return BAD_VALUE;
					}
					
					postRawData((char *)buf,size);
					reply->writeInt32(0);
					
					return NO_ERROR;
				}
				break;


			case SET_CALLBACK_TRANSACTION:{
					printf("set callback!\r\n");
					
					sp<ICallback> callback = interface_cast<ICallback>(data.readStrongBinder());
					reply->writeInt32(setCallback(callback));
					
					return NO_ERROR;
				}
				break;

			
			case START_CALLBACK_TRANSACTION: {
					printf("start callback!\r\n");
					CHECK_INTERFACE(INative, data, reply);

					startCallback();
					//reply->writeInt32(startCallback());
					
					return NO_ERROR;
				}
				break;

			case GET_VERSION_TRANSACTION:{
					printf("get version!\r\n");
					CHECK_INTERFACE(INative, data, reply);

					reply->writeCString(getVersion().c_str());
					
					return NO_ERROR;
				}
				break;

			case SET_VERSION_TRANSACTION:{
					printf("set version!\r\n");
					CHECK_INTERFACE(INative, data, reply);
					
					String8 version = data.readString8();
					
					printf("version222 = %s\r\n",version.string());
					ALOGI("version222 = %s\r\n",version.string());
					
					setVersion(version);
					
					return NO_ERROR;
				}
				break;
				
			default:
        	    return BBinder::onTransact(code, data, reply, flags);	
				break;
		}
		
		return NO_ERROR;
	}
		
	
	

}

