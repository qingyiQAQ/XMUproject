ifeq ($(USE_GCC), y)
CROSS_COMPILE = arm-linux-harmonyeabi-
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

else

LITEOS_SOURCE_TOP_DIR = /home/book/openharmony
CROSS_COMPILE := llvm-
CC  = clang
AS  = $(CROSS_COMPILE)as
AR  = $(CROSS_COMPILE)ar
LD  = ld.lld
GPP = clang++
OBJCOPY = $(CROSS_COMPILE)objcopy -R .bss
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE = $(CROSS_COMPILE)size
NM = $(CROSS_COMPILE)nm
STRIP = $(CROSS_COMPILE)strip

endif

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -Wall -O2 -g -target arm-liteos   --sysroot=$(LITEOS_SOURCE_TOP_DIR)/prebuilts/lite/sysroot/
CFLAGS += -I $(shell pwd)/include -I $(LITEOS_SOURCE_TOP_DIR)/third_party/freetype/include  -I $(LITEOS_SOURCE_TOP_DIR)/third_party/libjpeg/

LDFLAGS := -target arm-liteos   --sysroot=$(LITEOS_SOURCE_TOP_DIR)/prebuilts/lite/sysroot/ -L $(LITEOS_SOURCE_TOP_DIR)/out/ipcamera_hi3518ev300/libs/usr -lm -lfreetype -lpthread -ljpeg

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

TARGET := digitpic


obj-y += main.o
obj-y += display/
obj-y += encoding/
obj-y += fonts/
obj-y += input/
obj-y += debug/
obj-y += render/
obj-y += page/
obj-y += file/

all : 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) $(LDFLAGS) -o $(TARGET) built-in.o


clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
	
