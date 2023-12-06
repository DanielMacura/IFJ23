CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -lm -pedantic
LDFLAGS = -lm
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = ifj23
ARCHIVE = xmacur09.tgz

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@
	@rm -f $(OBJECTS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(EXECUTABLE) $(ARCHIVE)

.PHONY: clean test

test: $(EXECUTABLE)
	python3 tests/test.py ./$(EXECUTABLE)

final: $(EXECUTABLE)
	@rm -rf xmacur09
	mkdir xmacur09
	cp -r src/* Makefile documentation/dokumentace.pdf rozdeleni xmacur09/

	@sed -i 's/$(SRC_DIR)/./g' xmacur09/Makefile

	tar cvfz $(ARCHIVE) -C xmacur09 .

	@rm -rf xmacur09