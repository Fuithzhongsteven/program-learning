# Copyright 2005 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_C_INCLUDES += \
#	external/tinyalsa/include/
LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/tinyalsa/include/

LOCAL_SRC_FILES:= \
    tinyalsa/mixer.c \
    tinyalsa/pcm.c \
    dprintf.c \
    speecharraymini.c 

#LOCAL_SHARED_LIBRARIES:= libcutils libutils

LOCAL_CFLAGS += -Werror

LOCAL_MODULE:= libspeecharray

#LOCAL_SHARED_LIBRARIES := \
#    libtinyalsa 
    
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:=speecharraytest.c
LOCAL_SHARED_LIBRARIES := \
    libtinyalsa \
    libspeecharray
#LOCAL_C_INCLUDES += \
#	external/tinyalsa/include/
LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/tinyalsa/include/

    
LOCAL_MODULE:= speecharraytest    
LOCAL_SANITIZE := signed-integer-overflow
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:=findError.c
  
LOCAL_MODULE:= finderror    
LOCAL_SANITIZE := signed-integer-overflow
include $(BUILD_EXECUTABLE)


