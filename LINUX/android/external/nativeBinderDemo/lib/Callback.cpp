

#include "Callback.h"


// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"Callback"
#include	<cutils/log.h>
  
namespace android{
	int Callback::notifyCallback(uint8_t *buf,int len){
		int i;
		
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		ALOGI("len = %d\r\n",len);

		for(i=0;i<len;i++)
		{
			ALOGI("buf[%d] = 0x%x\r\n",i,buf[i]);
		}
		
		ALOGI("%s::---------------\r\n",__FUNCTION__);
		
		return 0;
	}

	status_t Callback::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
		
		return BnCallback::onTransact(code, data, reply, flags);
	}
}  

