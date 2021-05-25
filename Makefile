CC=gcc -elf_i386
AS=as --32
LD=ld -m elf_i386
CPP=cpp
AR=ar

OPTMZ?=-O2 -mtune=i386
DEBUG?=-g
WARNS=-Wall -Wextra -Wpedantic -Wstrict-aliasing \
	-Wno-pointer-arith -Wno-unused-parameter

LDFLAGS=-Ttext 0x7C00 --oformat=binary
CPPFLAGS=-pedantic -nostdinc -I.
CFLAGS=$(OPTMZ) $(DEBUG) $(WARNS) -m32 -nostdlib -nostdinc -I. \
	-fno-builtin-function -fno-builtin -ffreestanding -fno-pie \
	-fno-stack-protector -mno-red-zone

BOOTDIR=boot
BOOTSRC=$(BOOTDIR)/boot.S
BOOTOBJ=$(BOOTSRC:.S=.o)

LIBKDIR=libk
LIBKSRC=$(wildcard $(LIBKDIR)/*.c)
LIBKOBJ=$(LIBKSRC:.c=.o)

KRNLDIR=krnl
KRNLSRC=$(shell find $(KRNLDIR) -name '*.c' -or -name '*.S')
KRNLOBJ=$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(KRNLSRC)))

OUTDIR=bin
BOOTOUT=boot.bin
LIBKOUT=libk.a
KRNLOUT=krnl.bin
IMGOUT=krnl.img
ISOOUT=$(IMGOUT:.img=.iso)

all: prelude boot krnl img iso
	$(info compiled [$(BOOTSRC)] to [$(BOOTOBJ)])
	$(info compiled [$(KRNLSRC)] to [$(KRNLOBJ)])
	$(info compiled [$(LIBKSRC)] to [$(LIBKOBJ)])

prelude:
	mkdir -p $(OUTDIR) $(OUTDIR)/iso

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.S
	$(CPP) $(CPPFLAGS) $< | $(AS) -c -o $@

boot: $(BOOTOBJ)
	$(LD) -o $(OUTDIR)/$(BOOTOUT) $^ $(LDFLAGS)
	$(info compiled bootloader)

$(OUTDIR)/$(LIBKOUT): $(LIBKOBJ)
	$(AR) rcs $@ $^
	$(info compiled libk)

krnl: $(KRNLOBJ) $(OUTDIR)/$(LIBKOUT)
	$(LD) -o $(OUTDIR)/$(KRNLOUT) -T$(KRNLDIR)/link.ld $^
	$(info compiled kernel)

img: prelude boot krnl
	dd if=/dev/zero of=$(OUTDIR)/$(IMGOUT) bs=512 count=2880
	dd if=$(OUTDIR)/$(BOOTOUT) of=$(OUTDIR)/$(IMGOUT) \
		conv=notrunc bs=512 seek=0 count=1
	dd if=$(OUTDIR)/$(KRNLOUT) of=$(OUTDIR)/$(IMGOUT) \
		conv=notrunc bs=512 seek=1 count=2048
	$(info created img)

iso: img
	cp $(OUTDIR)/$(IMGOUT) $(OUTDIR)/iso
	mkisofs -V 'KRNL' -input-charset iso8859-1 -o $(OUTDIR)/$(ISOOUT) \
		-b $(IMGOUT) -hide $(IMGOUT) $(OUTDIR)/iso/
	$(info created iso)

.PHONY: clean
clean:
	rm -f $(OUTDIR)/$(BOOTOUT) $(OUTDIR)/$(LIBKOUT) $(OUTDIR)/$(KRNLOUT)
	rm -f $(OUTDIR)/$(IMGOUT) $(OUTDIR)/$(ISOOUT) $(OUTDIR)/iso/*
	find . -name '*.o' -exec rm {} +
