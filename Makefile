# based on the WinAVR makefile written by Martin Thomas, Eric B. Weddington, Jörg Wunsch, et al.
# Released to the Public Domain


# MCU name and submodel
MCU = arm7tdmi
SUBMDL = LPC2101
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork
Q =
Q = @

## Create ROM-Image (final)
RUN_MODE=ROM_RUN
## Create RAM-Image (debugging)
#RUN_MODE=RAM_RUN


# Output format. (can be srec, ihex, binary)
FORMAT = binary


# Target file name (without extension).
TARGET = main

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
SRC = system/system.c
#system/mystdio.c

# List C source files here which must be compiled in ARM-Mode.
# use file-extension c for "c-only"-files
SRCARM = system/vic.c

# List C++ source files here.
# use file-extension cpp for C++-files
CPPSRC = main.cpp

# List C++ source files here which must be compiled in ARM-Mode.
# use file-extension cpp for C++-files
CPPSRCARM = 

# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about< how the name is spelled on its command-line.
ASRC = 
ASRCARM = system/crt0.S

OPT = s
DEBUG = 3

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS = ./system

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options for C here
CDEFS =  -D$(RUN_MODE)

# Place -I options here
CINCS =

# Place -D or -U options for ASM here
ADEFS =  -D$(RUN_MODE)


# Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS) $(CINCS)
CFLAGS += -O$(OPT)
CFLAGS += -Wall -Wcast-align -Wcast-qual -Wimplicit #-fno-inline
CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
#CFLAGS += -Wa,-adhlns=$(<:.c=.lst) 
CFLAGS += -Wa,-adhlns=$(subst $(suffix $<),.lst,$<) 
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += -ffunction-sections
CFLAGS += -fno-exceptions

# flags only for C
#-Wmissing-prototypes -Wmissing-declarations
CONLYFLAGS =

# flags only for C++ (arm-elf-g++)
CPPFLAGS =

# Assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
##ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs 
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:.S=.lst),-g$(DEBUG)

#Additional libraries.

#Support for newlibc-lpc (file: libnewlibc-lpc.a)
#NEWLIBLPC = -lnewlib-lpc
NEWLIBCLPC =

MATH_LIB = -lm

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -nostartfiles -Wl,-Map=debug/main.map,--cref
LDFLAGS += -lc
LDFLAGS += $(NEWLIBLPC) $(MATH_LIB)
LDFLAGS += -lc -lgcc
#LDFLAGS += -Wl,--gc-sections

# Set Linker-Script Depending On Selected Memory
ifeq ($(RUN_MODE),RAM_RUN)
LINKERSCRIPT = system/$(SUBMDL)-RAM.ld
else
LINKERSCRIPT = system/$(SUBMDL)-ROM.ld
endif
LDFLAGS +=-T$(LINKERSCRIPT)

# Define programs and commands.
SHELL = sh
PREFIX = arm-none-eabi
CC = $(PREFIX)-g++
CPP = $(PREFIX)-g++
OBJCOPY = $(PREFIX)-objcopy
OBJDUMP = $(PREFIX)-objdump
SIZE = getsize.py
NM = $(PREFIX)-nm
REMOVE = rm -f
COPY = cp


# Define Messages
# English
MSG_FLASH =              "     HEX"
MSG_EXTENDED_LISTING =   "     LSS"
MSG_SYMBOL_TABLE =       "     SYM"
MSG_LINKING =            "      LD"
MSG_COMPILING =          "      CC"
MSG_COMPILING_ARM =      "   ARMCC"
MSG_COMPILINGCPP = 		 "     C++"
MSG_COMPILINGCPP_ARM =   "  ARMC++"
MSG_ASSEMBLING =         "      AS"
MSG_ASSEMBLING_ARM =     "   ARMAS"
MSG_CLEANING = Cleaning project:


# Define all object files.
COBJ      = $(SRC:.c=.o) 
AOBJ      = $(ASRC:.S=.o)
COBJARM   = $(SRCARM:.c=.o)
AOBJARM   = $(ASRCARM:.S=.o)
CPPOBJ    = $(CPPSRC:.cpp=.o) 
CPPOBJARM = $(CPPSRCARM:.cpp=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(ASRCARM:.S=.lst) $(SRC:.c=.lst) $(SRCARM:.c=.lst)
LST += $(CPPSRC:.cpp=.lst) $(CPPSRCARM:.cpp=.lst)

# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mcpu=$(MCU) $(THUMB_IW) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mcpu=$(MCU) $(THUMB_IW) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: sizebefore build sizeafter

build: elf hex lss sym

elf: debug/main.elf
hex: debug/main.hex
lss: debug/main.lss
sym: debug/main.sym

# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf
sizebefore:
	@if [ -f debug/main.elf ]; then cp debug/main.elf debug/main.old; fi

sizeafter:
	echo "WARNING: getsize.py doesn't support new filename scheme yet!"
	@$(SIZE) debug/main.elf


# Program the device.  
program: all hex
	@dd bs=1 count=20 if=debug/main.hex of=debug/main.bin 2>/dev/null
	@/bin/echo -n -e "\\0236\\0117\\0300\\0264" >> debug/main.bin
	@dd bs=1 seek=24 skip=24 if=debug/main.hex of=debug/main.bin 2>/dev/null
	@openocd -f system/flash.cfg -c program_flash -c shutdown

debug:
	cp debug/main.elf debug/debug.elf
	@openocd -f system/flash.cfg

ddd:
	ddd --debugger arm-none-eabi-gdb

reset:
	@openocd -f system/flash.cfg -c reset run -c shutdown

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(Q)$(OBJCOPY) -O $(FORMAT) $< $@


# Create extended listing file from ELF output file.
# testing: option -C
%.lss: %.elf
	$(Q)$(OBJDUMP) -h -S -C $< > $@


# Create a symbol table from ELF output file.
%.sym: %.elf
	$(Q)$(NM) -n $< > $@


# Link: create ELF output file from object files.
.SECONDARY : debug/main.elf
.PRECIOUS : $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(CPPOBJARM)
debug/main.elf:  $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(CPPOBJARM) $(LINKERSCRIPT)
	@echo $(MSG_LINKING) $@
	$(Q)$(CPP) $(THUMB) $(ALL_CFLAGS) $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(CPPOBJARM) --output $@ $(LDFLAGS)
#	$(CPP) $(THUMB) $(ALL_CFLAGS) $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(CPPOBJARM) --output $@ $(LDFLAGS)

# Compile: create object files from C source files. ARM/Thumb
$(COBJ) : %.o : %.c
	@echo $(MSG_COMPILING) $<
	$(Q)$(CC) -c $(THUMB) $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@ 

# Compile: create object files from C source files. ARM-only
$(COBJARM) : %.o : %.c
	@echo $(MSG_COMPILING_ARM) $<
	$(Q)$(CC) -c $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@ 

# Compile: create object files from C++ source files. ARM/Thumb
$(CPPOBJ) : %.o : %.cpp
	@echo $(MSG_COMPILINGCPP) $<
	$(Q)$(CPP) -c $(THUMB) $(ALL_CFLAGS) $(CPPFLAGS) $< -o $@ 

# Compile: create object files from C++ source files. ARM-only
$(CPPOBJARM) : %.o : %.cpp
	@echo $(MSG_COMPILINGCPP_ARM) $<
	$(Q)$(CPP) -c $(ALL_CFLAGS) $(CPPFLAGS) $< -o $@ 


# Compile: create assembler files from C source files. ARM/Thumb
## does not work - TODO - hints welcome
##$(COBJ) : %.s : %.c
##	$(CC) $(THUMB) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files. ARM/Thumb
$(AOBJ) : %.o : %.S
	@echo $(MSG_ASSEMBLING) $<
	$(Q)$(CC) -c $(THUMB) $(ALL_ASFLAGS) $< -o $@


# Assemble: create object files from assembler source files. ARM-only
$(AOBJARM) : %.o : %.S
	@echo $(MSG_ASSEMBLING_ARM) $<
	$(Q)$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Target: clean project.
clean:
	@echo $(MSG_CLEANING)
	$(REMOVE) debug/main.???
	$(REMOVE) $(COBJ)
	$(REMOVE) $(CPPOBJ)
	$(REMOVE) $(AOBJ)
	$(REMOVE) $(COBJARM)
	$(REMOVE) $(CPPOBJARM)
	$(REMOVE) $(AOBJARM)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) $(SRCARM:.c=.s)
	$(REMOVE) $(SRCARM:.c=.d)
	$(REMOVE) $(CPPSRC:.cpp=.s) 
	$(REMOVE) $(CPPSRC:.cpp=.d)
	$(REMOVE) $(CPPSRCARM:.cpp=.s) 
	$(REMOVE) $(CPPSRCARM:.cpp=.d)
	$(REMOVE) .dep/*
	$(REMOVE) *~

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

mmap: $(TARGET).elf
	$(Q)$(NM) -C -S -r --radix=d --size-sort $(TARGET).elf > $(TARGET).mmap.size
	$(Q)echo "upper: GLOBAL lower: local, B: BSS, D: Ram, T: code" > $(TARGET).smmap
	$(Q)cat $(TARGET).mmap.size | egrep -i "\ t\ " >> $(TARGET).smmap || true
	$(Q)cat $(TARGET).mmap.size | egrep -i "\ d\ " >> $(TARGET).smmap || true
	$(Q)cat $(TARGET).mmap.size | egrep -i "\ b\ " >> $(TARGET).smmap || true
	$(Q)rm $(TARGET).mmap.size
	$(Q)$(NM) -C -S --radix=d --numeric-sort $(TARGET).elf > $(TARGET).mmap.loc
	$(Q)cat $(TARGET).mmap.loc | egrep -i "\ t\ " > $(TARGET).lmmap || true
	$(Q)cat $(TARGET).mmap.loc | egrep -i "\ d\ " >> $(TARGET).lmmap || true
	$(Q)cat $(TARGET).mmap.loc | egrep -i "\ b\ " >> $(TARGET).lmmap || true


# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex lss sym clean clean_list program debug

%.bin: %.elf
	$(Q)$(OBJCOPY) -O binary $< $@
	
debug/main-checksum.bin: main.bin
	dd bs=1 count=20 if=main.bin of=debug/main-checksum.bin 2>/dev/null
	/bin/echo -n -e "\\0236\\0117\\0300\\0264" >> debug/main-checksum.bin
	dd bs=1 seek=24 skip=24 if=main.bin of=debug/main-checksum.bin 2>/dev/null
