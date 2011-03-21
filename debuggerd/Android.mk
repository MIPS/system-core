# Copyright 2005 The Android Open Source Project

BUILD_DEBUGGERD := false
ifeq ($(TARGET_ARCH),mips)
BUILD_DEBUGGERD := true
endif
ifeq ($(TARGET_ARCH),arm)
BUILD_DEBUGGERD := true
endif

ifeq ($(BUILD_DEBUGGERD),true)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= debuggerd.c getevent.c utility.c
ifeq ($(TARGET_ARCH),arm)
LOCAL_SRC_FILES += unwind-arm.c pr-support.c
endif
LOCAL_CFLAGS := -Wall
LOCAL_MODULE := debuggerd

ifeq ($(ARCH_ARM_HAVE_VFP),true)
LOCAL_CFLAGS += -DWITH_VFP
endif # ARCH_ARM_HAVE_VFP
ifeq ($(ARCH_ARM_HAVE_VFP_D32),true)
LOCAL_CFLAGS += -DWITH_VFP_D32
endif # ARCH_ARM_HAVE_VFP_D32

LOCAL_STATIC_LIBRARIES := libcutils libc

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := crasher.c
ifeq ($(TARGET_ARCH),arm)
LOCAL_SRC_FILES += crashglue.S
endif
ifeq ($(TARGET_ARCH),mips)
LOCAL_SRC_FILES += crashglue-mips.S
endif
LOCAL_MODULE := crasher
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_MODULE_TAGS := eng
#LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_SHARED_LIBRARIES := libcutils libc
include $(BUILD_EXECUTABLE)

ifeq ($(ARCH_ARM_HAVE_VFP),true)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -DWITH_VFP
ifeq ($(ARCH_ARM_HAVE_VFP_D32),true)
LOCAL_CFLAGS += -DWITH_VFP_D32
endif # ARCH_ARM_HAVE_VFP_D32

LOCAL_SRC_FILES := vfp-crasher.c vfp.S
LOCAL_MODULE := vfp-crasher
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_MODULE_TAGS := eng
LOCAL_SHARED_LIBRARIES := libcutils libc
include $(BUILD_EXECUTABLE)
endif # ARCH_ARM_HAVE_VFP == true

endif # BUILD_DEBUGGERD == true
