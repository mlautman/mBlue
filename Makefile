#------------------------------------------------------------------------------
# MAEVARM M4 STM32F373
# version: 1.0
# date: March 25, 2013
# author: Neel Shah (neels@seas.upenn.edu)
# description: Makefile for compilation of main code
#			   Auto detection of OS, tested with OSX, Ubuntu and Windows
#			   Auto find and addition of source files for compilation
#			   Multi Thread compilation by default for faster compilation
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# --> DON'T EDIT THIS FILE <--  
#------------------------------------------------------------------------------

MAKEFLAGS = -j

PROJNAME  = main
BUILDDIR  = obj
INCDIR    = inc
LIBDIR    = lib
SOURCEDIR = src

ARMDIR   = arm
CPALDIR  = cpal
DSPDIR   = dsp
STDIR    = st
USBDIR   = usb

ifeq ($(OS),Windows_NT)
	UNAME := Windows
	SHELL=c:/windows/system32/cmd.exe
else
    UNAME := $(shell uname -s)
endif

ARCH = arm-none-eabi
CC = $(ARCH)-gcc
LD = $(ARCH)-ld
AS = $(ARCH)-as
OBJCPY = $(ARCH)-objcopy
OBJDMP = $(ARCH)-objdump

LDSCRIPT = $(LIBDIR)/$(STDIR)/STM32_FLASH.ld
STARTUP  = $(LIBDIR)/$(STDIR)/startup_stm32f37x.s 

CFLAGS  = -g -Os -std=c99
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -I$(INCDIR) -I$(LIBDIR)/$(ARMDIR) -I$(LIBDIR)/$(CPALDIR)/$(INCDIR)
CFLAGS += -I$(LIBDIR)/$(STDIR)/$(INCDIR) -I$(LIBDIR)/$(USBDIR)/$(INCDIR)
CFLAGS += -DARM_MATH_CM4 -D'__FPU_PRESENT=1' 
#CFLAGS += -DUSE_STDPERIPH_DRIVER
#CFLAGS += -mthumb-interwork

LDFLAGS  = $(CFLAGS)
LDFLAGS += --static -Wl,--gc-sections
LDFLAGS += -nostartfiles -T$(LDSCRIPT)

AFLAGS  = -mlittle-endian -mthumb -mcpu=cortex-m4 
ODFLAGS	= -x --syms
CPFLAGS = --output-target=binary

_SRCS = $(wildcard $(SOURCEDIR)/*.c)
_SRCS += $(wildcard *.c)
SRCS = $(notdir $(_SRCS))
SRCS += startup_stm32f37x.s

_OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCS))
OBJS = $(patsubst %.s,$(BUILDDIR)/%.o,$(_OBJS))

ifeq ($(UNAME),Windows)
_OBJSW = $(patsubst %.c,%.o,$(SRCS))
OBJSW = $(patsubst %.s,%.o,$(_OBJSW))
endif
#------------------------------------------------------------------------------

.PHONY: $(LIBDIR)/$(BUILDDIR)/libstm32f37x.a proj

all: proj
	@echo "[>--BinaryGenerated--<]" 
	
$(LIBDIR)/$(BUILDDIR)/libstm32f37x.a:
	@echo "[>Library Compilation<]"
	@$(MAKE) -C $(LIBDIR)
ifeq ($(UNAME),Windows)
	@If Not Exist "$(CURDIR)/$(BUILDDIR)" (mkdir "$(CURDIR)/$(BUILDDIR)")
else
	@mkdir -p $(BUILDDIR)
endif
	@echo "[>--CodeCompilation--<]"

proj: $(BUILDDIR)/$(PROJNAME).elf
	

$(BUILDDIR)/$(PROJNAME).elf: $(LIBDIR)/$(BUILDDIR)/libstm32f37x.a $(OBJS)
	@$(CC) $(LDFLAGS) $^ -o $@ -L$(LIBDIR)/$(BUILDDIR) -lstm32f37x
	@$(OBJCPY) $(CPFLAGS) $(BUILDDIR)/$(PROJNAME).elf $(BUILDDIR)/$(PROJNAME).bin
ifeq ($(UNAME),Windows)
	@$(OBJCPY) --output-target=ihex $(BUILDDIR)/$(PROJNAME).elf $(BUILDDIR)/$(PROJNAME).hex
endif

disassemble: lib proj
	@$(OBJDMP) $(ODFLAGS) $(BUILDDIR)/$(PROJNAME).elf > $(BUILDDIR)/$(PROJNAME).dmp
	@$(OBJDMP) -dS $(BUILDDIR)/$(PROJNAME).elf > $(BUILDDIR)/$(PROJNAME).dis

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
$(BUILDDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/startup_stm32f37x.o: $(STARTUP)
ifeq ($(UNAME),Windows)
	@$(AS) $(AFLAGS) "$(CURDIR)/$(STARTUP)" -o "$(CURDIR)/$@"
else
	@$(AS) $(AFLAGS) $(STARTUP) -o $@
endif
	
flash: all
	@echo "[>-Downloading to M4-<]"
ifeq ($(UNAME),Windows)
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D "$(CURDIR)/$(BUILDDIR)/$(PROJNAME).bin"
endif
ifeq ($(UNAME),Linux)
	@ls -l $(BUILDDIR)/$(PROJNAME).bin
	@sudo dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D $(BUILDDIR)/$(PROJNAME).bin
endif
ifeq ($(UNAME),Darwin)
	@ls -l $(BUILDDIR)/$(PROJNAME).bin
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D $(BUILDDIR)/$(PROJNAME).bin
endif
	@echo "[>-----M4 Loaded-----<]"  
	
clean:
ifeq ($(UNAME),Windows)
	@erase $(OBJSW) /s 
	@erase $(PROJNAME).dmp $(PROJNAME).dis $(PROJNAME).elf $(PROJNAME).hex $(PROJNAME).bin /s
else
	@rm -f $(BUILDDIR)/*.o $(BUILDDIR)/*.lst $(BUILDDIR)/*.map $(BUILDDIR)/*.dmp $(BUILDDIR)/*.dis \
	$(BUILDDIR)/$(PROJNAME).elf $(BUILDDIR)/$(PROJNAME).hex $(BUILDDIR)/$(PROJNAME).bin
endif
	
cleanlib: clean
	@$(MAKE) clean -C lib 

#------------------------------------------------------------------------------
