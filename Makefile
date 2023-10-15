CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -lm -pedantic
LDFLAGS = -lm
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
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
	
