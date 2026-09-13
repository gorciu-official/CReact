CC       := emcc
CFLAGS   := $(shell tr '\n' ' ' < compile_flags.txt)

SRC_DIR   := src
BUILD_DIR := obj

SRCS := $(shell find src ../src -name '*.c')

OBJS := $(patsubst src/%.c,obj/%.o,$(filter src/%.c,$(SRCS))) \
        $(patsubst ../src/%.c,obj/%.o,$(filter ../src/%.c,$(SRCS)))

TARGET := web/creact.js

all: $(TARGET)

$(TARGET): $(OBJS)
	@envsubst < web/index.html.template > web/index.html
	@if [[ -d ../assets ]]; then ln -sfn ../../assets web/assets; fi
	$(CC) -sSINGLE_FILE=1 $(OBJS) -o $@

obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: ../src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
