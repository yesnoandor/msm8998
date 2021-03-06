LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libutils \
	liblog  \
	libbinder

LOCAL_MODULE := libINativeBinder

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \

LOCAL_SRC_FILES:= \
	NativeService.cpp \
	INativeService.cpp \
	Callback.cpp \
	ICallback.cpp \
	depthEvaluate.cpp \
	ProcessThread.cpp \
	DepthSensor.cpp \
	NdkThread.cpp \
	NdkTxThread.cpp \
	UsbHid.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
