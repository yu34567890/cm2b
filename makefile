CC = gcc


WARNFLAGS = -Wall -Wextra


DEBUG_FLAGS = $(WARNFLAGS) -O0  -g
PROD_FLAGS  = $(WARNFLAGS) -O2 -DNDEBUG

SRCS := $(wildcard *.c)


MODE ?= debug

ifeq ($(MODE),debug)
    CFLAGS = $(DEBUG_FLAGS)
    BUILD_DIR = build/Debug
    TARGET = $(BUILD_DIR)/outDebug
else ifeq ($(MODE),production)
    CFLAGS = $(PROD_FLAGS)
    BUILD_DIR = build/Release
    TARGET = $(BUILD_DIR)/outProd
else
    $(error Unknown build mode '$(MODE)'; use MODE=debug or MODE=production)
endif

OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf build


debug:
	$(MAKE) MODE=debug

production:
	$(MAKE) MODE=production

.PHONY: all clean debug production
