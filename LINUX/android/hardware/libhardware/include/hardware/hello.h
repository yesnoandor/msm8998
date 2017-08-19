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

#ifndef _HARDWARE_HELLO_H
#define _HARDWARE_HELLO_H

#include <hardware/hardware.h>

__BEGIN_DECLS

#define HELLO_API_VERSION HARDWARE_MODULE_API_VERSION(1,0)

/**
 * The id of this module
 */
#define HELLO_HARDWARE_MODULE_ID "hello"

/**
 * The id of the main hello device
 */
#define HELLO_DEVICE_ID_MAIN "main_hello"

struct hello_device;
typedef struct hello_device {
    /**
     * Common methods of the hello device.  This *must* be the first member of
     * hello_device as users of this structure will cast a hw_device_t to
     * hello_device pointer in contexts where it's known the hw_device_t references a
     * hello_device.
     */
    struct hw_device_t common;

    /** Set the value
     *
     * What happens when this function is called while the the timeout of a
     * previous call has not expired is implementation dependent.
     *
     * @param value to set
     *
     * @return 0 in case of success, negative errno code else
     */
    int (*set_val)(struct hello_device* hellodev, int val);

    /** Get the value
     *
     * It is not guaranteed that the hello will be immediately stopped: the
     * behaviour is implementation dependent.
     *
     * @return 0 in case of success, negative errno code else
     */
    int (*get_val)(struct hello_device* hellodev, int * val);
} hello_device_t;

static inline int hello_dev_open(const struct hw_module_t* module, hello_device_t** device)
{
    return module->methods->open(module, HELLO_DEVICE_ID_MAIN, (struct hw_device_t**)device);
}

__END_DECLS

#endif  // _HARDWARE_HELLO_H

#if 0
#ifndef ANDROID_HELLO_INTERFACE_H
#define ANDROID_HELLO_INTERFACE_H
#include <hardware/hardware.h>

__BEGIN_DECLS

/*定义模块ID*/
#define HELLO_HARDWARE_MODULE_ID "hello"

/*硬件模块结构体*/
struct hello_module_t {
	struct hw_module_t common;
};

/*硬件接口结构体*/
struct hello_device_t {
	struct hw_device_t common;
	int fd;
	int (*set_val)(struct hello_device_t* dev, int val);
	int (*get_val)(struct hello_device_t* dev, int* val);
};

__END_DECLS

#endif
#endif
