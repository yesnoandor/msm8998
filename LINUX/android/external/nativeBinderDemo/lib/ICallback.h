/*
* 
*
*/



#ifndef ICALLBACK_H    
#define ICALLBACK_H

using namespace android;

namespace android{
	// ����callback  �ӿ�ICallback
	class ICallback : public IInterface{
		public:
			// ������һЩ���룬����
		    // ������ֶ�descriptor��
		    // �����������Ա����asInterface��getInterfaceDescriptor
			// ����˹�������������
			DECLARE_META_INTERFACE(Callback);

			// �ýӿڶ����ṩ�Ĳ����ӿ�
			virtual int notifyCallback(uint8_t *buf,int len) = 0;
	};

	// ����ö��ICallback	�ӿڵ����з���
	enum {
		NOTIFY_CALLBACK_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
	};

	// ����callback  ��ʵ����BnCallback, �̳�BnInterface
	class BnCallback : public BnInterface<ICallback>{
		public:
			virtual status_t    onTransact( uint32_t code,  
                                    const Parcel& data,  
                                    Parcel* reply,  
                                    uint32_t flags = 0);
	};

	// ����callback  �ӿڵ�������BpCallback, �̳�BpInterface
	class BpCallback: public BpInterface<ICallback> {
		public:
			BpCallback(const sp<IBinder>& impl);
			
			virtual int notifyCallback(uint8_t *buf,int len);
	};
}

#endif 

