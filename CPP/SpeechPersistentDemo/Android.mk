LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := UBTSpeechPersistent.c threadpool.c UBTSpeechDemo.c

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE := SpeechDemo

include $(BUILD_EXECUTABLE)
