

# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hello.default

# HAL module implementation stored in
# hw/<HELLO_HARDWARE_MODULE_ID>.default.so
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_C_INCLUDES := hardware/libhardware
LOCAL_SRC_FILES := hello.c
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)


##----------------------------------
#LOCAL_PATH := $(call my-dir)
#include $(CLEAR_VARS)

#LOCAL_MODULE_TAGS := optional

#LOCAL_PRELINK_MODULE := false
#LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
#LOCAL_SHARED_LIBRARIES := liblog libcutils
#LOCAL_SRC_FILES := hello.c
#LOCAL_MODULE := hello.default

#LOCAL_32_BIT_ONLY := true

#include $(BUILD_SHARED_LIBRARY)

