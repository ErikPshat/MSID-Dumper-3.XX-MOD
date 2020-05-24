TARGET = mstest
OBJS = main.o ../res/mdumper_prx.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = ../lib
LDFLAGS = 
LIBS = -lpspdebug

PSP_FW_VERSION = 271

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = MSID Dumper 3.xx MOD RUS
PSP_EBOOT_ICON = ../res/ICON0.PNG
BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak