CC = /home/chester/wujf/code/test/Firefly-RK3308_Linux_SDK_git_20190924/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc
#CC = aarch64-linux-gnu-gcc
#CC = gcc

CFLAGS = -I. -O0 -g -ggdb

CFLAGS += -I./../src/common -I./../src/net -I./../src/prt -I./../src/tools

LDFLAGS = -I. -L. -L./../src/prt -lesc2bmp -lpthread -ldl

#DEPS = ./../src/esc2bmp.h

SRCS = ./../src/main.c

include ./../src/common/common.mk
include ./../src/net/net.mk
include ./../src/prt/prt.mk
include ./../src/tools/tools.mk


OBJS = $(patsubst %.c, %.o, $(SRCS))


TARGET = d9main

#all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

	adb push ./d9main /oem

%.o:%c 
	$(CC) ${CFLAGS} -c $< -o $@

clean:
	mv ./../src/tools/sqlite3.o ./../src/tools/sqlite3.bak
	rm -rf $(OBJS) $(TARGET)
	mv ./../src/tools/sqlite3.bak ./../src/tools/sqlite3.o
