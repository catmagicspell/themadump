TARGET = themadump
SRCDIR = ./source
INCDIR = ./include
LIBDIR = ./library
RESDIR = ./resource

CFILES := $(wildcard $(SRCDIR)/*.c)
OBJS := $(CFILES:.c=.o)

CFLAGS = -Ofast -w
LIBS = -lpspexploit -lpsprtc
USE_PSPSDK_LIBC = 1
USE_PSPSDK_LIBS = 1

BUILD_PRX = 1
PSP_FW_VERSION = 370
PSP_LARGE_MEMORY = 0

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = ThemaDump
PSP_EBOOT_ICON= $(RESDIR)/ICON0.png
#PSP_EBOOT_PIC1= $(RESDIR)/PIC1.png
#PSP_EBOOT_SND0= $(RESDIR)/SND0.at3

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak