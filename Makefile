.PHONY: all clean run

CC := gcc
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -g

SOURCES := src/jsiss.c src/main.c
OBJECTS := $(SOURCES:src/%.c=build/%.o)
DEPS := $(OBJECTS:.o=.d)

all: build/app

clean:
	rm -rf build

run: build/app
	./build/app

build:
	mkdir -p build

build/app: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

build/%.o: src/%.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)
