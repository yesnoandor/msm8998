/*
 * Copyright (C) 2009 The Android Open Source Project
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

#define LOG_TAG "HelloService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/hello.h>

#include <stdio.h>

namespace android
{
	/*��Ӳ��������ж����Ӳ�����ʽṹ�壬�ο�<hardware/hello.h>*/
 	struct hello_device* hello_device = NULL;
	
	/*ͨ��Ӳ������㶨���Ӳ�����ʽӿ�����Ӳ���Ĵ���val��ֵ*/
	static void hello_setVal(JNIEnv* env, jobject clazz, jint value) {
		int val = value;
		
		ALOGI("HelloService JNI: set value %d to device.", val);
		if(!hello_device) {
			ALOGI("Hello JNI: device is not open.");
			return;
		}
		
		hello_device->set_val(hello_device, val);
	}
 	
	/*ͨ��Ӳ������㶨���Ӳ�����ʽӿڶ�ȡӲ���Ĵ���val��ֵ*/
	static jint hello_getVal(JNIEnv* env, jobject clazz) {
		int val = 0;

		ALOGI("HelloService JNI: get value from device.");

		if(!hello_device) {
			ALOGI("HelloService JNI: device is not open.");
			return val;
		}
		hello_device->get_val(hello_device, &val);
		
		ALOGI("HelloService JNI: get value %d from device.", val);
	
		return val;
	}
        
	/*ͨ��Ӳ������㶨���Ӳ��ģ��򿪽ӿڴ�Ӳ���豸*/
	static inline int hello_device_open(const hw_module_t* module, struct hello_device** device) {
		int ret;
		
		ALOGI("hello_device_open::+++++++++++++++");
		
		ret = module->methods->open(module, HELLO_HARDWARE_MODULE_ID, (struct hw_device_t**)device);

		ALOGI("hello_device_open::---------------");
		
		return ret;
	}


 	/*ͨ��Ӳ��ģ��ID������ָ����Ӳ�������ģ�鲢��Ӳ��*/
	static jboolean hello_init(JNIEnv* env, jclass clazz) {
		hw_module_t* module;
		
		ALOGI("HelloService JNI: initializing......");

		if(hw_get_module(HELLO_HARDWARE_MODULE_ID, (const hw_module_t**)&module) == 0) {
			ALOGI("HelloService JNI: hello Stub found.");
			
			if(hello_device_open(module, &hello_device) == 0) {
				ALOGI("HelloService JNI: hello device is open.");
				return JNI_TRUE;
			}
			
			ALOGE("HelloService JNI: failed to open hello device.");
			return JNI_FALSE;
		}
		
		ALOGE("HelloService JNI: failed to get hello stub module.");
		return JNI_FALSE;		
	}

	/*JNI������*/
	static const JNINativeMethod method_table[] = {
		{"init_native", "()Z", (void*)hello_init},
		{"setVal_native", "(I)V", (void*)hello_setVal},
		{"getVal_native", "()I", (void*)hello_getVal},
	};

	/*ע��JNI����*/
	int register_android_server_HelloService(JNIEnv *env) {
        ALOGI("HelloService JNI: register......");
    	return jniRegisterNativeMethods(env, "com/android/server/HelloService", method_table, NELEM(method_table));
	}

};
