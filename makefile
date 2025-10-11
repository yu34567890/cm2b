CC = gcc
CFLAGS = -Wall -Wextra -O2
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, build/%.o, $(SRCS))
TARGET = build/program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build
clean:
	rm -rf build

.PHONY: all clean build
