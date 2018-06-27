#ifndef USBHID_H
#define USBHID_H


//#include	"NdkThread.h"

//#include 	<string>

//using namespace std;

//#include	"INativeService.h"
//#include	"NativeService.h"


namespace android {


class NdkThread;
class NativeService;

using namespace std;


static const string USB_HID_DEVICE_NAME =	"/dev/hidg0";

class UsbHid : public RefBase
{
public:
	//UsbHid();
	UsbHid(sp<NativeService> service,string name = USB_HID_DEVICE_NAME);
	
	~UsbHid();

//private:
public:

	bool open_device(string name = "/dev/hidg0");
	void close_device();
	
	bool set_feature_report(uint8_t* data, uint32_t len);
	bool get_feature_report(uint8_t* data, uint32_t len);
	
	bool write_hid_report(uint8_t* data, uint32_t len);
	uint32_t read_hid_report(uint8_t* data, uint32_t len);

//private:
public:
	int m_hid_fd;
	string m_hid_name;

	sp<NdkThread> mNdkThread;
	sp<NativeService> mNativeService;
};


}



#endif
