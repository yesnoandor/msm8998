LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog  \
	libbinder \
	libINativeBinder

LOCAL_MODULE := nativeBinderServer
LOCAL_SRC_FILES:= \
	nativeBinderServer.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

