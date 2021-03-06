# Hey Emacs, this is a -*- makefile -*-

# AVR-GCC Makefile template, derived from the WinAVR template (which
# is public domain), believed to be neutral to any flavor of "make"
# (GNU make, BSD make, SysV make).
#
# Relying on GNU make features now as I can't stand the compatible
# make deficiencies.
#
# GNUmakefile structure:
#   1. Variable definitions
#   2. Default target
#   3. Explicit rules
#   4. Implicit/pattern rules and phony targets


MKDIR_P = mkdir -p


CFLAGS =
CLEANFILES =
FIRMWARE_OBJ =
COMMON_X =

#include ../common.mk

# Define local settings by defining them in settings.mk. For an example of
# settings to define in settings.mk, see the settings.mk.sample
# file.
#
# If you have not defined the required things in your local
# settings.mk, the build will abort with an appropriate error message.
-include settings.mk

# Function to mark required settings.mk variables
DEFINITION_REQUIRED = \
	$(if $($(1)),\
	$(info LOCAL: $(1)=$($(1))),\
	$(error LOCAL build config variable $(1) is undefined. You may want to add/uncomment a few lines in your settings.mk file (copy settings.mk.sample if settings.mk does not exist)))

# List of all required LOCAL build config variables settings.mk needs
# to define.
$(call DEFINITION_REQUIRED,AVRDUDE_PORT)
$(call DEFINITION_REQUIRED,AVRDUDE_PROGRAMMER)
$(call DEFINITION_REQUIRED,F_CPU)
$(call DEFINITION_REQUIRED,MCU)

# End of local settings


# The firmware format we eventually feed to avrdude
FORMAT = ihex


########################################################################
# Compilation flags


# Optimize for size (or whatever gcc understands by that)
CFLAGS += -Os


# Our source code requires the F_CPU macro to be defined at all times
CPPFLAGS += -DF_CPU=$(F_CPU)


# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
CFLAGS += -gstabs


# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CFLAGS += -std=gnu99


# Place -D or -U options here
# CPPFLAGS +=


# Place -I options here
#CPPFLAGS += -I../include


CPPFLAGS += -Wall -Wextra
# The file scope definition of register variables used in uart-ringbuf-global.h
# does not allow for -pedantic
# CPPFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wstrict-prototypes
# Some more flags that might be useful for tuning:
# CFLAGS += -funsigned-char
# CFLAGS += -funsigned-bitfields

# Pack structure members together without holes
# CFLAGS += -fpack-struct

# Use 8bit integers for enum values (insted of standard int size)
CFLAGS += -fshort-enums

# Use only 8bit for the stack pointer
# CFLAGS += -mtiny-stack

# Violates the C standard, but gives sizeof(int) == sizeof(char) == 1
# (segfaults the compiler)
# CFLAGS += -mint8

# Generate error on multiple definition of variable without "extern"
CFLAGS += -fno-common

# Save temporary files (useful e.g. for debugging inline asm problems)
CFLAGS += -save-temps

# Put extra commentary into the generated assembly code
# CFLAGS += -fverbose-asm

# Never generate code which refers to register r7
# CFLAGS += -ffixed-r7

# Called functions may clobber register r8
# CFLAGS += -fcall-used-r8

# Caller must save register r8
# CFLAGS += -fcall-saved-r9

# Make function prologues/epilogues subroutine calls
# (smaller code size? not really.)
# CFLAGS += -mcall-prologues

# Generate listing file
# CFLAGS += -Wa,-adhlns=$(<:.c=.lst)


ASFLAGS += -Wa,-adhlns=$(<:.S=.lst),-gstabs


# Add target processor to flags.
CPPFLAGS += -mmcu=$(MCU)


CPPFLAGS += -I.
ASFLAGS += -x assembler-with-cpp


########################################################################
# Link flags


# Additional libraries.

# Minimalistic printf version
# LDLIBS += -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
# LDLIBS += -Wl,-u,vfprintf -lprintf_flt

# Minimalistic scanf version
# LDLIBS += -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
# LDLIBS += -Wl,-u,vfscanf -lscanf_flt

# Math library
LDLIBS += -lm

# External memory options

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
# LDFLAGS += -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
# LDFLAGS += -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x80ffff

# Create map file on linking
LDFLAGS += -Wl,-Map=$(@:.elf=.map),--cref


########################################################################
# The programs used

AWK = gawk
SED = sed
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
OD = od


########################################################################
# Programming support using avrdude.

AVRDUDE_WRITE_FLASH = -U flash:w:firmware.hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:firmware.eep

# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_BASIC =
AVRDUDE_BASIC += -p $(MCU)
AVRDUDE_BASIC += -P $(AVRDUDE_PORT)
AVRDUDE_BASIC += -c $(AVRDUDE_PROGRAMMER)

AVRDUDE_FLAGS =
AVRDUDE_FLAGS += $(AVRDUDE_BASIC)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)


########################################################################
# Default target

.PHONY: all
all: elf hex lss sym fuses checks

# Legacy target
.PHONY: ALL
ALL: all


########################################################################
# Optional firmware features



########################################################################
# Link firmware image


# Define the common object files.
# The object files specific to firmware personalities will not be listed here.
FIRMWARE_OBJ += .objs/main.o
FIRMWARE_OBJ += .objs/unrelated-sources.o

# IMPORTANT:
# All the registers mentioned here MUST be the same set as in the
# uart-ringbuf-global.h register variable definitions.
CFLAGS += -ffixed-r13
CFLAGS += -ffixed-r14
CFLAGS += -ffixed-r15
FIRMWARE_OBJ += .objs/uart-ringbuf.o


# Link time checks
# LDFLAGS += -Wl,--verbose
LDFLAGS += -Wl,--defsym=RAM_END=$(RAM_END)
LDFLAGS += -Wl,--defsym=MAX_RUNTIME_STACK_SIZE=$(MAX_RUNTIME_STACK_SIZE)
LDFLAGS += -Wl,--defsym=MALLOC_HEAP_SIZE=$(MALLOC_HEAP_SIZE)

# Check that (data+stack) fit into SRAM with a linker script ASSERT().
# Requires RAM_END and MAX_RUNTIME_STACK_SIZE to be --defsym'd.
# COMMON_X += check-data-stack-in-SRAM.x


# ======================================================================
# Firmware image
firmware.elf : $(FIRMWARE_OBJ) $(COMMON_X)
firmware.elf : .objs/main.o
firmware.elf : .objs/uart-ringbuf.o
	$(LINK.c) $^ $(LDLIBS) --output $@


########################################################################
# "metatargets"

.PHONY: elf hex eep lss sym fuses
elf: firmware.elf
hex: firmware.hex
eep: firmware.eep
lss: firmware.lss
sym: firmware.sym
fuses: firmware.fuses


########################################################################
# AVR fuse extraction, reading, writing, comparing

CLEANFILES += firmware.fuses
CLEANFILES += firmware.lfuse.txt
CLEANFILES += firmware.hfuse.txt
CLEANFILES += firmware.efuse.txt
firmware.fuses: firmware.elf
	$(OBJCOPY) -j .fuse -O binary $< $@
	@chmod -x $@
	@echo "Split $@ into $*.{l,h,e}fuse.txt"; \
	$(OD) -A n -t xC $@ | \
	{ read lfuse hfuse efuse restofline; \
	  echo "0x$$lfuse" > firmware.lfuse.txt; \
	  echo "0x$$hfuse" > firmware.hfuse.txt; \
	  echo "0x$$efuse" > firmware.efuse.txt; \
	}

compare-fuses: read-fuses firmware.fuses
	@echo "New fuse values to be written to device:"; \
	for f in lfuse hfuse efuse; do \
		echo "    $$f=$$(cat "firmware.$$f.txt")"; \
	done

program-fuses: firmware.fuses
	@echo "Writing fuses to device:"; \
	for f in lfuse hfuse efuse; do \
		echo "    $$f=$$(cat "firmware.$$f.txt")"; \
	done
	$(AVRDUDE) $(AVRDUDE_FLAGS) -u \
		-U lfuse:w:$(shell cat firmware.lfuse.txt):m \
		-U hfuse:w:$(shell cat firmware.hfuse.txt):m \
		-U efuse:w:$(shell cat firmware.efuse.txt):m

read-fuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS) \
		-U lfuse:r:DEVICE.lfuse.txt:h \
		-U hfuse:r:DEVICE.hfuse.txt:h \
		-U efuse:r:DEVICE.efuse.txt:h
	@echo "Read fuses from device:"; \
	for f in lfuse hfuse efuse; do \
		echo "    $$f=$$(cat "DEVICE.$$f.txt")"; \
	done


########################################################################
# Check the firmware images


# The 0x00800000 is avr-gcc's Harvard architecture trick, and the
# first 0x100 bytes in the addr space are CPU and IO registers, after
# which the 4K of SRAM start, up to and including address 0x10ff.
RAM_END = 0x00801100

# Size of memory area we reserve for malloc(3)
MALLOC_HEAP_SIZE = 64

# The maximum expected stack size expected at runtime is the stack
# size we want to be sure to have space for. We just estimate this
# value, but we have a consistency check lower down in the form of the
# check-min-stack-size.check target.
MAX_RUNTIME_STACK_SIZE = 256

# Check that the minimum stack size we want accomodated in a firmware
# (used for other checks) is actually less than the number of push
# instructions in the firmware image. As the firmwares do not use
# recursion, the push instruction count is a good upper bound estimate
# for the stack depth.
CHECKS += min-stack-size
check-min-stack-size.check: firmware.lss
	@set -e; \
	CALL_INSTRUCTION_COUNT="$$(grep -E "\s[0-9a-f]+:\s.*\scall\s" $< | wc -l)"; \
	RCALL_INSTRUCTION_COUNT="$$(grep -E "\s[0-9a-f]+:\s.*\srcall\s" $< | wc -l)"; \
	ALL_CALL_INSTRUCTION_COUNT="$$(expr "$$CALL_INSTRUCTION_COUNT" + "$$RCALL_INSTRUCTION_COUNT")"; \
	PUSH_INSTRUCTION_COUNT="$$(grep -E "\s[0-9a-f]+:\s.*\spush\sr[0-9]+" $< | wc -l)"; \
	TOTAL_COUNT="$$(expr "$$ALL_CALL_INSTRUCTION_COUNT" + "$$PUSH_INSTRUCTION_COUNT")"; \
	echo "CHECK($*): PUSH_COUNT+2*CALL_COUNT=$$PUSH_INSTRUCTION_COUNT+2*$$ALL_CALL_INSTRUCTION_COUNT=$$TOTAL_COUNT <= MAX_RUNTIME_STACK_SIZE=$(MAX_RUNTIME_STACK_SIZE)"> $@; \
	test "$$TOTAL_COUNT" -le "$(MAX_RUNTIME_STACK_SIZE)" || { cat $@; exit 1; }

check-ALL.check: $(foreach CHECK, $(CHECKS), check-$(CHECK).check)
	@cat $^ > $@

check-ALL: check-ALL.check
	@cat $<

# The awk magic sums up the numbers from the text and data columns,
# i.e. the total amount of bytes that need to be flashed to the chip,
# and shows them under the new "txt+dat" column.
.PHONY: checks
checks: check-ALL
	@$(SIZE) firmware.elf \
	| $(AWK) '($$1 ~ /^[0-9]+$$/) { s=$$1+$$2; printf "%7d\t%s\n", s, $$0; next; } { printf "%7s\t%s\n", "txt+dat", $$0; }'


########################################################################
# Firmware image formats and firmware image statistics

FIRMWARE_FORMATS += hex
firmware.hex: firmware.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse $< $@

# FIRMWARE_FORMATS += eep
# firmware.eep: firmware.elf
# 	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
# 		--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
FIRMWARE_FORMATS += lss
firmware.lss: firmware.elf
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
FIRMWARE_FORMATS += sym
firmware.sym: firmware.elf
	$(NM) -n $< > $@


########################################################################
# Program the device with a firmware image

.PHONY: program
program: $(foreach FORMAT, $(FIRMWARE_FORMATS), firmware.$(FORMAT)) check-ALL
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)


########################################################################
# Compilation rules

# Compile: create object files from C source files.
.objs/%.o: %.c .deps/%.c.dep
	@$(MKDIR_P) $(@D)
	$(COMPILE.c) $< -o $@


# Assemble: create object files from assembler source files.
.objs/%.o: %.S .deps/%.S.dep
	@$(MKDIR_P) $(@D)
	$(CC) -c $(ASFLAGS) $(CPPFLAGS) $< -o $@


########################################################################
# Automatic dependency generation

.deps/%.S.dep: %.S
	@set -e; rm -f $@; \
		$(MKDIR_P) $(@D); \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		$(SED) 's,\($*\)\.o[ :]*,.objs/\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

.deps/%.c.dep: %.c
	@set -e; rm -f $@; \
		$(MKDIR_P) $(@D); \
		$(COMPILE.c) -MM $< > $@.$$$$; \
		$(SED) 's,\($*\)\.o[ :]*,.objs/\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(foreach F, $(wildcard *.c *.S), .deps/$(F).dep)


########################################################################
# clean target

.PHONY: clean
clean:
	rm -f $(CLEANFILES)
	rm -f $(FIRMWARE_OBJ) $(OTHER_OBJ)
	rm -f *.hex *.eep *.cof *.elf *.map *.sym *.lss
	rm -f check-*.check
	rm -f *.lst
	rm -f *.i
	rm -f *.o
	rm -f *.s
	rm -f *~
	rm -rf .deps .objs


########################################################################
# End of GNUmakefile
