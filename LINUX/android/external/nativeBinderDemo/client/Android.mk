LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog  \
	libbinder \
	libINativeBinder

LOCAL_MODULE := nativeBinderClient
LOCAL_SRC_FILES:= \
	nativeBinderClient.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)



