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
	@if [ -d ../assets ]; then rm -rf web/assets && cp -r ../assets web/assets; fi
	$(CC) $(OBJS) -o $@
	sed -i 's/creact\.wasm/creact.txt/g' web/creact.js
	mv web/creact.wasm web/creact.txt

obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: ../src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
