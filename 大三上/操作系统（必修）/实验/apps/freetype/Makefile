
LITEOS_SOURCE_TOP_DIR = /home/book/openharmony

all:
	clang -target arm-liteos   --sysroot=$(LITEOS_SOURCE_TOP_DIR)/prebuilts/lite/sysroot/  \
-I $(LITEOS_SOURCE_TOP_DIR)/third_party/freetype/include \
-L $(LITEOS_SOURCE_TOP_DIR)/out/ipcamera_hi3518ev300/libs/usr  \
-lfreetype \
-o show_line show_line.c

clean:
	rm -f show_line
