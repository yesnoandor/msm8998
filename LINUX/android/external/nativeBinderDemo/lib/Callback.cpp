#if 0
#include <binder/Parcel.h>  
#include <binder/IPCThreadState.h>  
#include <utils/String16.h>  
#include <utils/threads.h>  
#include <utils/Atomic.h>  
  
//#include <cutils/bitops.h>  
#include <cutils/properties.h>  
#include <cutils/compiler.h>
#endif

#include "Callback.h"  
  
namespace android{
	int Callback::notifyCallback(uint8_t *buf,int len){
		int i;
		
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

		printf("len = %d\r\n",len);

		for(i=0;i<len;i++)
		{
			printf("buf[%d] = 0x%x\r\n",i,buf[i]);
		}
		
		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
		
		return 0;
	}

	status_t Callback::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
		printf("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
		printf("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
		
		return BnCallback::onTransact(code, data, reply, flags);
	}
}  

