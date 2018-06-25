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
	// ����service  �ӿ�INativeService
	class INativeService : public IInterface
	{			
		public:
		    // ������һЩ���룬����
		    // ������ֶ�descriptor��
		    // �����������Ա����asInterface��getInterfaceDescriptor
			// ����˹�������������
			DECLARE_META_INTERFACE(NativeService);
	        
	        // �÷�������ṩ�Ĳ����ӿ�
			virtual int add(int a,int b)=0;		// �ӷ�����
			virtual int postRawData(char * buf,int length) = 0;			// ����ԭʼ����

			virtual int setCallback(const sp<ICallback>& callback) = 0;		// ���ûص�
			virtual void startCallback() = 0;								// �����ص�

			virtual string getVersion() = 0;
			virtual void setVersion(String8 version) = 0;
	};


	// ����ö��INativeService	�ӿڵ����з���
	enum{ 
		ADD_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
		POST_RAW_DATA_TRANSACTION,
		SET_CALLBACK_TRANSACTION,
		START_CALLBACK_TRANSACTION,
		GET_VERSION_TRANSACTION,
		SET_VERSION_TRANSACTION,
	};
			

	// ����binder  �����ʵ����BnNativeService, �̳�BnInterface
	class BnNativeService: public BnInterface<INativeService> {
		public:
			virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,uint32_t flags = 0);
	};


	// ����binder  �����������BpNativeService, �̳�BpInterface
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
