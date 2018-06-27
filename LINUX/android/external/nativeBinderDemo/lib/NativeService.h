/****************************************Copyright (c)**************************************************                         
**  
** 		
********************************************************************************************************/
#ifndef NATIVE_SERVICE_H
#define NATIVE_SERVICE_H

#include "INativeService.h"
#include "DepthSensor.h"
#include "UsbHid.h"

namespace android {

/*
struct DepthPoint
{
    float x;                 //!< X coordinate [meters]
    float y;                 //!< Y coordinate [meters]
    float z;                 //!< Z coordinate [meters]
    float noise;             //!< noise value [meters]
    short int grayValue;      //!< 16-bit gray value
    signed char depthConfidence; //!< value from 0 (invalid) to 255 (full confidence)
};
*/

/*
typedef struct
{
	struct DepthPoint data[224 * 172];
}depth_frame_t;
*/

class NativeService : public BnNativeService
{
    friend class BinderService<NativeService>;    // for MediaLogService()
	
	public:
		static void instantiate();
	
    	virtual int add(int a,int b);
		virtual int postRawData(char * buf,int len);
		virtual int setCallback(const sp<ICallback>& callback);
		virtual void startCallback();	
		virtual string getVersion();
		virtual void setVersion(String8 version);

	public:
		NativeService();
		//sp<ICallback> mCallback;
		vector<sp<ICallback>> mCallback;

		//std::list<depth_frame_t *> dataQueue;

		DepthSensor * mDepthSensor;
		String8 mVersion;
		
		sp<UsbHid> mUsbHid;
    
	public:
    	virtual ~NativeService();

};




}; // namespace android

#endif

