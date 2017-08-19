/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/hello.h>
#include <hardware/hardware.h>

#define LOG_TAG "HelloStub"
#include <cutils/log.h>

#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#define		DEVICE_NAME				"/dev/hello"
//#define	DEVICE2_NAME			"/sys/class/hello/hello/val"

static int hello_exists() {
    int fd;

	if(open(DEVICE_NAME, O_RDWR) == -1) {
		ALOGE("Hello Stub: failed to open %s -- %s.", DEVICE_NAME,strerror(errno));
		return 0;
	}

	ALOGI("open device success!!!!");	

    close(fd);
    return 1;
}

static int hello_set_val(struct hello_device* hellodev __unused, int val)
{
	int len,ret, fd;

 	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    fd = TEMP_FAILURE_RETRY(open(DEVICE_NAME, O_RDWR));
    if(fd < 0) {
        return -errno;
    }
	

    ALOGI("val = 0x%x\r\n",val);
	
    len = TEMP_FAILURE_RETRY(write(fd, &val, sizeof(val)));

    ALOGI("len = %d\r\n",len);

    if (len == -1) {
        ret = -errno;
    } else if (len != sizeof(val)) {
        /* even though EAGAIN is an errno value that could be set
           by write() in some cases, none of them apply here.  So, this return
           value can be clearly identified when debugging and suggests the
           caller that it may try to call vibraror_on() again */
        ret = -EAGAIN;
    } else {
        ret = 0;
    }

    errno = 0;
    close(fd);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return ret;
}


static int hello_get_val(struct hello_device* hellodev __unused,int *val)
{
	int len, ret, fd;

    //char value[20]; /* large enough for millions of years */

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    fd = TEMP_FAILURE_RETRY(open(DEVICE_NAME, O_RDWR));
    if(fd < 0) {
        return -errno;
    }

    len = TEMP_FAILURE_RETRY(read(fd, val, sizeof(*val)));
    ALOGI("val = 0x%x\r\n",*val);

    if (len == -1) {
        ret = -errno;
    } else if (len != sizeof(val)) {
        /* even though EAGAIN is an errno value that could be set
           by write() in some cases, none of them apply here.  So, this return
           value can be clearly identified when debugging and suggests the
           caller that it may try to call vibraror_on() again */
        ret = -EAGAIN;
    } else {
        ret = 0;
    }

    errno = 0;
    close(fd);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return ret;
}

static int hello_close(hw_device_t *device)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    free(device);

    ALOGI("%s::---------------\r\n",__FUNCTION__);
    
    return 0;
}

static int hello_open(const hw_module_t* module, const char* id __unused,
                      hw_device_t** device __unused) {
                      
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
    
    if (!hello_exists()) {
        ALOGE("Hello device does not exist. Cannot start vibrator");
        return -ENODEV;
    }

    hello_device_t *hellodev = calloc(1, sizeof(hello_device_t));

    if (!hellodev) {
        ALOGE("Can not allocate memory for the hello device");
        return -ENOMEM;
    }

    hellodev->common.tag = HARDWARE_DEVICE_TAG;
    hellodev->common.module = (hw_module_t *) module;
    hellodev->common.version = HARDWARE_DEVICE_API_VERSION(1,0);
    hellodev->common.close = hello_close;

    hellodev->set_val = hello_set_val;
    hellodev->get_val = hello_get_val;

    *device = (hw_device_t *) hellodev;

    ALOGI("%s::---------------\r\n",__FUNCTION__);

    return 0;
}

/*===========================================================================*/
/* Default hello HW module interface definition                           */
/*===========================================================================*/

static struct hw_module_methods_t hello_module_methods = {
    .open = hello_open,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .module_api_version = HELLO_API_VERSION,
    .hal_api_version = HARDWARE_HAL_API_VERSION,
    .id = HELLO_HARDWARE_MODULE_ID,
    .name = "Default hello HAL",
    .author = "The Android Open Source Project",
    .methods = &hello_module_methods,
};

#if 0
#include <hardware/hardware.h>
#include <hardware/hello.h>
#include <fcntl.h>
#include <errno.h>
#include <cutils/atomic.h>

#define LOG_TAG "HelloStub"
#include <cutils/log.h>


#define DEVICE_NAME "/dev/hello"
#define MODULE_NAME "Hello"
#define MODULE_AUTHOR "shyluo@gmail.com"

/*设备打开和关闭接口*/
static int hello_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device);
static int hello_device_close(struct hw_device_t* device);

/*设备访问接口*/
static int hello_set_val(struct hello_device_t* dev, int val);
static int hello_get_val(struct hello_device_t* dev, int* val);

/*模块方法表*/
static struct hw_module_methods_t hello_module_methods = {
	open: hello_device_open
};

/*模块实例变量*/
struct hello_module_t HAL_MODULE_INFO_SYM = {
	common: {
		tag: HARDWARE_MODULE_TAG,
		version_major: 1,
		version_minor: 0,
		id: HELLO_HARDWARE_MODULE_ID,
		name: MODULE_NAME,
		author: MODULE_AUTHOR,
		methods: &hello_module_methods,
	}
};

static int hello_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device) {
	struct hello_device_t* dev;

    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
    
	dev = (struct hello_device_t*)malloc(sizeof(struct hello_device_t));    
	if(!dev) {
		ALOGE("Hello Stub: failed to alloc space");
		return -EFAULT;
	}

	memset(dev, 0, sizeof(struct hello_device_t));
	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (hw_module_t*)module;
	dev->common.close = hello_device_close;
	dev->set_val = hello_set_val;dev->get_val = hello_get_val;

	if((dev->fd = open(DEVICE_NAME, O_RDWR)) == -1) {
		ALOGE("Hello Stub: failed to open /dev/hello -- %s.", strerror(errno));free(dev);
		return -EFAULT;
	}

	*device = &(dev->common);
	ALOGI("Hello Stub: open /dev/hello successfully.");

    ALOGI("%s::---------------\r\n",__FUNCTION__);

	return 0;
}

static int hello_device_close(struct hw_device_t* device) {
	struct hello_device_t* hello_device = (struct hello_device_t*)device;

    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
    
	if(hello_device) {
		close(hello_device->fd);
		free(hello_device);
	}

    ALOGI("%s::---------------\r\n",__FUNCTION__);
    
	return 0;
}

static int hello_set_val(struct hello_device_t* dev, int val) {
	ALOGI("Hello Stub: set value %d to device.", val);

    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

    ALOGI("val = 0x%x\r\n",val);
    
	write(dev->fd, &val, sizeof(val));

    ALOGI("%s::---------------\r\n",__FUNCTION__);

	return 0;
}

static int hello_get_val(struct hello_device_t* dev, int* val) {
    
    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
    
	if(!val) {
		ALOGE("Hello Stub: error val pointer");
		return -EFAULT;
	}

	read(dev->fd, val, sizeof(*val));

    ALOGI("val = 0x%x\r\n",*val);

	ALOGI("Hello Stub: get value %d from device", *val);

    ALOGI("%s::---------------\r\n",__FUNCTION__);
     
	return 0;
}
#endif
