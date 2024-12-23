all: retrojuuyon.z64
.PHONY: all

CFLAGS += \
	-O2 -funroll-loops \
	-std=c89 -Wall -Wextra \
	-Ilibretro-common/include

BUILD_DIR = build
SRC_DIR = src
include $(N64_INST)/include/n64.mk

OBJS = \
	$(BUILD_DIR)/src/audio.o \
	$(BUILD_DIR)/src/core.o \
	$(BUILD_DIR)/src/environment.o \
	$(BUILD_DIR)/src/input.o \
	$(BUILD_DIR)/src/main.o \
	$(BUILD_DIR)/src/retrojuuyon.o \
	$(BUILD_DIR)/src/video.o

# Get the current git version
GIT_VERSION := $(shell git describe --tags --dirty --always)

# Define the N64 ROM title with the git version
N64_ROM_TITLE_WITH_VERSION := "retrojuuyon $(GIT_VERSION)"

retrojuuyon.z64: N64_ROM_TITLE = $(N64_ROM_TITLE_WITH_VERSION)

$(BUILD_DIR)/retrojuuyon.elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)
