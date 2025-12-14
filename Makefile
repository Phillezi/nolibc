CC := gcc

# Directories
SRC_DIR   := src
LIB_DIR   := $(SRC_DIR)/nostd
BUILD_DIR := build

# Output binary
TARGET := nostdlib

# Source files
LIB_SRCS := \
	$(LIB_DIR)/lib.c \
	$(LIB_DIR)/string.c \
	$(LIB_DIR)/sys.c \
	$(LIB_DIR)/stdio.c

APP_SRCS := \
	$(SRC_DIR)/main.c

SRCS := $(LIB_SRCS) $(APP_SRCS)

# Object files
OBJS := \
	$(BUILD_DIR)/nostd/lib.o \
	$(BUILD_DIR)/nostd/string.o \
	$(BUILD_DIR)/nostd/sys.o \
	$(BUILD_DIR)/nostd/stdio.o \
	$(BUILD_DIR)/main.o

# Compiler flags
CFLAGS := \
	-nostdlib \
	-nostartfiles \
	-nodefaultlibs \
	-ffreestanding \
	-mno-red-zone \
	-static \
	-fno-stack-protector \
	-fno-pie \
	-no-pie \
	-fno-builtin \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Os \
	-s \
	-ffunction-sections \
	-fomit-frame-pointer \
	-fdata-sections \
	-fno-unwind-tables \
	-fno-asynchronous-unwind-tables

# Linker flags
LDFLAGS := -nostdlib -static -Wl,-e,_start -Wl,--gc-sections -Wl,--build-id=none -Wl,--strip-all -Wl,--hash-style=gnu

ifeq ($(CC),gcc)
	LDFLAGS += -Wl,--nmagic -Wl,--no-relax
endif

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS)  -o $@

# Compile rules
$(BUILD_DIR)/nostd/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/nostd
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
