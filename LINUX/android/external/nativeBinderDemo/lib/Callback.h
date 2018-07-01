#include "../include/common.h"
#include "INativeService.h" 
#include "ICallback.h"

//#include <binder/BinderService.h>  


typedef void (*flxndkMsgCallbackFunc)(int msg_id, void * msg_buf, int msg_len);


namespace android{
	class Callback: public BnCallback{  
		friend class BinderService<Callback>;

		public:
			virtual int notifyCallback(uint8_t *buf,int len);
			virtual     status_t    onTransact(  
                                uint32_t code,  
                                const Parcel& data,  
                                Parcel* reply,  
                                uint32_t flags); 

			virtual void registerOnMessage(flxndkMsgCallbackFunc callback);

		private:
			flxndkMsgCallbackFunc onMessageFunc;
	};  
}  

