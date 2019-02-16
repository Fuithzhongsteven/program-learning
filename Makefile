# Makefile for libutils; based on core/libutils/Android.mk

#/home/zxh/tools/android-ndk-r13b-standalone-arm-gcc/android-24
CROSS_TOOLS_HOME=/home/zxh/tools/
SYSROOT = $(CROSS_TOOLS_HOME)/android-ndk-r13b-standalone-arm-gcc/android-24/sysroot
LINUX_NDK_HOME =$(CROSS_TOOLS_HOME)/android-ndk-r13b-standalone-arm-gcc/android-24/bin

CC  = $(LINUX_NDK_HOME)/aarch64-linux-android-gcc
LD  = $(LINUX_NDK_HOME)/aarch64-linux-android-ld
CPP = $(LINUX_NDK_HOME)/aarch64-linux-android-cpp
CXX = $(LINUX_NDK_HOME)/aarch64-linux-android-g++
AR  = $(LINUX_NDK_HOME)/aarch64-linux-android-ar
AS  = $(LINUX_NDK_HOME)/aarch64-linux-android-as
NM  = $(LINUX_NDK_HOME)/aarch64-linux-android-nm
STRIP = $(LINUX_NDK_HOME)/aarch64-linux-android-strip


TOP_DIR = $(shell pwd)
INSTALL_DIR = $(TOP_DIR)/install
INCLUDES_DIR = $(TOP_DIR)/includes
OUT_DIR = $(TOP_DIR)/out

#LIBS_DIR = $(TOP_DIR)/libs
#RES_DIR = $(TOP_DIR)/res
THIRD_DIR = $(TOP_DIR)/third_party


LOCAL_FLAGS := -Werror -fsigned-char 
LOCAL_FLAGS += -O2 -Wno-unused-variable
LOCAL_FLAGS += -rdynamic -g -DDEBUG
LOCAL_FLAGS += -I $(SYSROOT)/usr/include --sysroot=$(SYSROOT)
#LOCAL_FLAGS += -mcpu=cortex-a72.cortex-a53+crypto -mtune=cortex-a72.cortex-a53
#LOCAL_FLAGS += -Wl,--as-needed -DHAVE_PTHREADS

LOCAL_CFLAGS := -Wall  
#LOCAL_LDFLAGS +=  -L$(LIBS_DIR)
LOCAL_LDFLAGS += -L$(SYSROOT)/usr/lib64 -L$(SYSROOT)/usr/lib --sysroot=$(SYSROOT)

#LOCAL_CPPFLAGS := -std=gnu++11
#LOCAL_CFLAGS += -fsanitize=address -fno-omit-frame-pointer
#LOCAL_CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer
#LOCAL_LIBS := -lz -lcrypto -lrt -ldl -lpthread
#LOCAL_LDFLAGS := -O2 -Wl,--hash-style=gnu,--as-needed 

LOCAL_INCLUDE := -I$(INCLUDES_DIR)

CPP_FLAGS := $(LOCAL_FLAGS) $(LOCAL_CPPFLAGS)
C_FLAGS := $(LOCAL_FLAGS) $(LOCAL_CFLAGS)
LDFLAGS := $(LOCAL_LDFLAGS) 
INCS := $(LOCAL_INCLUDE)

all: libspeecharray speecharraytest

##############################################################################################
#libspeecharray speecharraytest
##############################################################################################
SPEECH_DIR=$(TOP_DIR)/speech
SPEECH_INC=$(SPEECH_DIR)/include

SPEECH_SRC := $(wildcard $(SPEECH_DIR)/src/*.c) 
SPEECH_OBJS := $(patsubst %.c,%.o,$(SPEECH_SRC))


$(SPEECH_OBJS):%o:%c
	@$(CC) -shared -fPIC -o $@ -c $<  $(C_FLAGS) $(INCS) -I$(SPEECH_INC) $(LDFLAGS)

libspeecharray:$(SPEECH_OBJS)
	@echo begin compile $@
	@$(CC) -shared -fPIC -o $(OUT_DIR)/$@.so $^  $(C_FLAGS) $(INCS) $(LDFLAGS)
	@echo done compile $@

libspeecharray-clean:
	@echo clean libspeecharray
	@rm -rf $(OUT_DIR)/libspeecharray.so $(SPEECH_OBJS)

#####################################################################
speechtest_SRC := $(SPEECH_DIR)/test/speecharraytest.c
speechtest_OBJS := $(SPEECH_DIR)/test/speecharraytest.o

$(speechtest_OBJS):%o:%c
	@$(CC) -o $@ -c $<  $(C_FLAGS) $(INCS) -I$(SPEECH_INC) $(LDFLAGS) -L$(OUT_DIR) -lspeecharray

speecharraytest:$(speechtest_OBJS)
	@echo begin compile $@
	@$(CC) -o $(OUT_DIR)/$@ $^ $(INCS) -I$(SPEECH_INC) $(LDFLAGS) $(C_FLAGS) -L$(OUT_DIR) -lspeecharray
	@echo done compile $@

speecharraytestclean:
	@echo clean speecharraytest
	@rm -rf $(speechtest_OBJS) speecharraytest

##############################################################################################


clean: speecharraytestclean libspeecharray-clean
	@echo clean done 

install:
	@echo install





