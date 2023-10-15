CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -lm -pedantic
LDFLAGS = -lm
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = ifj23

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@
	@rm -f $(OBJECTS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: clean test

test: $(EXECUTABLE)
	python3 tests/test.py ./$(EXECUTABLE)
