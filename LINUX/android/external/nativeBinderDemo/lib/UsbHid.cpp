#include	"../include/common.h" 

#include	"INativeService.h"
#include	"NativeService.h"
#include	"NdkThread.h"
#include	"NdkTxThread.h"

#include	"UsbHid.h"

// ----------------- Declaration Debug Zone ----------------
#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NativeService"
#include	<cutils/log.h>

using namespace std;

// ----------------- Macr Define -------------------------


//hid_service::hid_service()
//{
//	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

//	m_hid_name = USB_HID_DEVICE_NAME;

//	ALOGI("%s::---------------\r\n",__FUNCTION__);
//}
namespace android {

UsbHid::UsbHid(sp<NativeService> service,string name)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	//mNativeService = service;
	m_hid_name = name;
	mNativeService = service;

	UsbHid::open_device();
	
	//mNativeService->mCallback;
	mNdkThread = new NdkThread(this);
	mNdkThread->start();

	mNdkTxThread = new NdkTxThread(this);
	mNdkTxThread->start();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

UsbHid::~UsbHid()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
	
bool UsbHid::open_device(string name)
{
	bool ret = true;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    m_hid_fd = open(name.c_str(),O_RDWR);
    if (m_hid_fd < 0){
        ALOGE("failed to open usb hid device(%s)",name.c_str());
        ret = false;
    }

    ALOGI("%s::---------------\r\n",__FUNCTION__);

    return ret;
}

void UsbHid::close_device()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	if(m_hid_fd > 0)
        close(m_hid_fd);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

bool UsbHid::set_feature_report(uint8_t* data, uint32_t len)
{
	
#if 0
    if(m_hid_fd < 0)
        return false;
    uint8_t reportID = data[0];
    if(reportID == 0)
    {
        data++;
        length++;
    }
    int r = ioctl(fd, HIDIOCSETFEAURE(length),data);
    return (r>=0);
#endif

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return true;
}

bool UsbHid::get_feature_report(uint8_t* data, uint32_t len)
{
#if 0
    if(fd<0)
        return false;
    int r = ioctl(fd, HIDIOCGETFEAURE(length),data);
    return (r>=0);
#endif

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return true;
}

bool UsbHid::write_hid_report(uint8_t* data, uint32_t len)
{
	bool ret = false;
	ssize_t size = 0;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	if(m_hid_fd)
	{
		size = write(m_hid_fd,data,len);
		if(size > 0)
		{
			ALOGI("len = %d",len);
    		ALOGI("size = %d",static_cast<int>(size));

    		ret = true;
		}
	}

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return (ret);
}

uint32_t UsbHid::read_hid_report(uint8_t* data, uint32_t len)
{
	bool ret = false;
    ssize_t size = 0;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	if(m_hid_fd)
	{
		size = read(m_hid_fd,data,len);
		if(size > 0)
		{
			ALOGI("len = %d",len);
			ALOGI("size = %d",static_cast<int>(size));

			ret = true;
		}
	}

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return	(size);
}


void UsbHid::push_back(msg_t * item)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	mNdkTxQueue.push_back(item);
	mNdkTxThread->notify();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

msg_t * UsbHid::pop_front()
{
	msg_t * item;
	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	item = mNdkTxQueue.front();
	mNdkTxQueue.pop_front();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return item;
}


bool UsbHid::empty()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return mNdkTxQueue.empty();
}

}

#if 0
static	pthread_t	uhid_thread_id;
static	pthread_mutex_t uhid_lock;

#define	UHID_BUFFER_SIZE	1024

static void * uhid_loop_func(void *arg)  
{
	fd_set readfds;
	int uhid_exit = 0;

	int i;
	int maxfd,fd;
	int ret;
	ssize_t size;
	
	uint8_t buf[UHID_BUFFER_SIZE*2];
	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);


	//NdkService::instantiate();
	NdkService * mNdkService = new NdkService();
	defaultServiceManager()->addService(String16("service.native"),mNdkService);

	// 
	hid_service * uhid = new hid_service();

	uhid->open_device();

	while (!uhid_exit){

		size = 0;
		maxfd = 0;
		maxfd = fd = uhid->m_hid_fd;

		FD_ZERO(&readfds);
		
		FD_SET(fd, &readfds);

		ret = select(maxfd + 1, &readfds, NULL, NULL, NULL);
		switch(ret)
		{
			case -1:
				//exit = 1;
				ALOGE("usb hid select failed!(err = %s)\r\n",strerror(errno));
				break;
				
			case 0:
				ALOGW("usb hid select timeout!\r\n");
				break;
		
			default:
				ALOGI("get data event!\r\n");
				if (FD_ISSET(fd, &readfds))
				{
					size = uhid->read_hid_report(buf, sizeof(buf));
					if(size < 0)
					{	
						ALOGE("socket (%d) recv failed!(size = %ld,err = %s)\r\n",i,size,strerror(errno));
						break;
					}
					else if(size == 0)
					{
						ALOGW("socket(%d) disconnect\r\n",i);
						continue;
					}
					else	
					{
						ssize_t len = 0;

						ALOGI("size = %ld\r\n",size);
						for(i=0;i<size;i++)
						{
							ALOGI("buf[%d] = 0x%x\r\n",i,buf[i]);
						}


						sp<INdkCallback> c = mNdkService->mCallback;

		
    					c->notifyCallback(buf,sizeof(buf));  
    	
						//while(len < size)
						//{
						//	ALOGI("str = %s\r\n",buf + len);
						
							
						//	ALOGI("len = %ld\r\n",len);
						//}
					}		
					
				}
				break;
		}

	}

	uhid->close_device();


	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return 0;
}


void uhid_server_start(void)
{
	int err;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	

	// thread init	
	pthread_mutex_init(&uhid_lock, NULL);
	
	err = pthread_create(&uhid_thread_id, NULL, uhid_loop_func, NULL);
    if(err != 0)
    {
    	ALOGE("create uhid thread error: %s\r\n",strerror(err));  
		return;
	}

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
#endif
