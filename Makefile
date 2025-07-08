AS=nasm
ASM_PREFIX=asm_
ASM_EXTENSION=asm

LD=ld
LD_SCRIPT=link.ld

CC=gcc
CFLAGS=-Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c
CEXTRA=-Werror -Wextra -Wall
CDEFS=
C_PREFIX=
C_EXTENSION=c

CPPC=gcc
CPPFLAGS=$(CFLAGS) -fno-exceptions -fno-rtti
CPPEXTRA=$(CEXTRA)
CPPDEFS=
CPP_PREFIX=cc_
CPP_EXTENSION=cc


#directories
OUT_DIR=out
ISO_DIR=$(OUT_DIR)/iso
KERNEL_DIR=kernel
LOADER_DIR=boot
BINARY_DIR=bin

#kernel sources
KERNEL_SRC=$(shell find $(KERNEL_DIR) -name '*.$(C_EXTENSION)')
KERNEL_ASM=$(shell find $(KERNEL_DIR) -not -name 'inc_*.$(ASM_EXTENSION)' -name '*.$(ASM_EXTENSION)')
KERNEL_CPP=$(shell find $(KERNEL_DIR) -name '*.$(CPP_EXTENSION)')

#kernel objects
KERNEL_OBJ=$(addprefix $(OUT_DIR)/$(C_PREFIX), $(notdir $(KERNEL_SRC:.$(C_EXTENSION)=.o)))
KERNEL_OBJ+=$(addprefix $(OUT_DIR)/$(ASM_PREFIX), $(notdir $(KERNEL_ASM:.$(ASM_EXTENSION)=.o)))
KERNEL_OBJ+=$(addprefix $(OUT_DIR)/$(CPP_PREFIX), $(notdir $(KERNEL_CPP:.$(CPP_EXTENSION)=.o)))

#main targets
TARGET_ISO=$(OUT_DIR)/nectix.iso
TARGET_RAW=$(OUT_DIR)/nectix.bin
TARGET_KERNEL=$(OUT_DIR)/kernel.elf
TARGET_LOADER=$(OUT_DIR)/loader.bin

#sub targets
SUB_EXPANDED=$(OUT_DIR)/expanded.o
SUB_BINARY=$(OUT_DIR)/binary.o
SUB_FLOPPY=nectix.img

#deps targets
DEP_BOOT=$(wildcard $(LOADER_DIR)/*.$(ASM_EXTENSION))


all:: $(TARGET_ISO)


$(TARGET_ISO): $(TARGET_RAW)
	dd if=/dev/zero of=$(OUT_DIR)/$(SUB_FLOPPY) bs=1024 count=1440
	dd if=$< of=$(OUT_DIR)/$(SUB_FLOPPY) seek=0 count=1 conv=notrunc
	mkdir -p $(ISO_DIR)
	cp $(OUT_DIR)/$(SUB_FLOPPY) $(ISO_DIR)
	mkisofs -quiet -V 'nectix' -input-charset iso8859-1 \
	-o $@ -b $(SUB_FLOPPY) -hide $(SUB_FLOPPY) $(ISO_DIR)


$(TARGET_RAW): $(TARGET_LOADER) $(TARGET_KERNEL)
	cat $^ > $@


$(TARGET_LOADER): $(LOADER_DIR)/loader.$(ASM_EXTENSION) $(DEP_BOOT)
	$(AS) -fbin -o $@ $<


#link object in order
$(TARGET_KERNEL): $(SUB_EXPANDED) $(SUB_BINARY) $(KERNEL_OBJ)
	$(LD) -T$(LD_SCRIPT) -o $@ $^


#kernel automatic sources
$(OUT_DIR)/$(C_PREFIX)$(notdir %.o): $(KERNEL_DIR)/%.$(C_EXTENSION)
	$(CC) $(CFLAGS) $(CEXTRA) $(CDEFS) -o $@ $<


$(OUT_DIR)/$(CPP_PREFIX)$(notdir %.o): $(KERNEL_DIR)/%.$(CPP_EXTENSION)
	$(CPPC) $(CPPFLAGS) $(CPPEXTRA) $(CPPDEFS) -o $@ $<


$(OUT_DIR)/$(ASM_PREFIX)$(notdir %.o): $(KERNEL_DIR)/%.$(ASM_EXTENSION)
	$(AS) -felf64 -o $@ $<


#expanded bootloader space
$(SUB_EXPANDED): $(LOADER_DIR)/expanded.$(ASM_EXTENSION) $(DEP_BOOT)
	$(AS) -felf64 -o $@ $<


#included binaries
$(SUB_BINARY): $(BINARY_DIR)/binary.$(ASM_EXTENSION)
	$(AS) -felf64 -o $@ $<


.PHONY: clean
clean:
	rm -f $(TARGET_ISO) $(TARGET_RAW) $(TARGET_LOADER) $(TARGET_KERNEL) \
	$(SUB_EXPANDED) $(SUB_BINARY) $(KERNEL_OBJ) \
	$(OUT_DIR)/$(SUB_FLOPPY) $(ISO_DIR)/$(SUB_FLOPPY)


#qemu opts
QEMU_SYSTEM=qemu-system-x86_64
QEMU_DRIVE=-drive format=raw,file=$<,if=floppy,index=0
QEMU_OPTS=-m 256M -monitor stdio


.PHONY: qemu
qemu: $(TARGET_RAW)
	$(QEMU_SYSTEM) $(QEMU_OPTS) $(QEMU_DRIVE)


#bochs opts
BOCHS_CONFIG=.bochsrc
BOCHS_OPTS=-q


.PHONY: bochs
bochs: $(TARGET_RAW)
	bochs $(BOCHS_OPTS) -f $(BOCHS_CONFIG)
