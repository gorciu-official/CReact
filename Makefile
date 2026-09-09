CC       := emcc
CFLAGS   := $(shell tr '\n' ' ' < compile_flags.txt)

SRC_DIR   := src
BUILD_DIR := obj

SRCS := $(shell find $(SRC_DIR) ../src -name '*.c')
OBJS := $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))

TARGET := web/creact.js

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.o:
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(filter %/$*.c,$(SRCS)) -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
