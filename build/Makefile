## Compilers and other tools ###################################################
## * Don't use normal gcc, use the arm cross compiler
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

## CPU and Architecture names ##################################################
CPU = cortex-a7
ARCH = arm
IMAGE = kernel7

## Flags #######################################################################
C_FLAGS = -msoft-float -std=c11 -mcpu=$(CPU) -fpic -ffreestanding -g
# Prevent the compiler from assuming that null pointers are invalid.
# Now that we're the operating system, 0x0 actually contains useful data for us!
C_FLAGS += -fno-delete-null-pointer-checks
SRC_FLAGS = -O1 -Wall -Wextra
L_FLAGS = -ffreestanding -O1 -nostdlib

## Location of files ###########################################################
HDR_DIR = ../include
SRC_DIR = ../src
OBJ_DIR = objects

HEADERS = $(wildcard $(HDR_DIR)/*.h) $(wildcard $(HDR_DIR)/*/*.h) $(wildcard $(HDR_DIR)/*/*/*.h)
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
ASSMBLS = $(wildcard $(SRC_DIR)/*.s) $(wildcard $(SRC_DIR)/*/*.s) $(wildcard $(SRC_DIR)/*/*/*.s)

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
OBJECTS += $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASSMBLS))
OBJECTS += objects/bootimg.o

LD_SCRIPT = linker.ld

## Build rules #################################################################
build: $(OBJECTS) $(HEADERS)
	$(CC) -T $(LD_SCRIPT) -o $(IMAGE).elf $(L_FLAGS) $(OBJECTS)
	$(OBJCOPY) $(IMAGE).elf -O binary $(IMAGE).img

objects/bootimg.o: $(SRC_DIR)/bootimg.bin
	$(OBJCOPY) -I binary -O elf32-littlearm -B $(ARCH) $< $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -I$(SRC_DIR) -I$(HDR_DIR) -c $< -o $@ $(SRC_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm $(IMAGE).elf
	rm $(IMAGE).img

run: build
	qemu-system-$(ARCH) -m 1G -M raspi2b -serial stdio -kernel $(IMAGE).elf

debug: build
	qemu-system-$(ARCH) -m 1G -M raspi2b -serial stdio -s -S -kernel $(IMAGE).elf

all: build