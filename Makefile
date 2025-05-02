# Compiler et options
CC = gcc
CFLAGS = -Wall -Wextra
DEBUG_FLAGS = -g
RELEASE_FLAGS = -Werror

SRC = src/common.c src/comm_serie.c
INCLUDES = src/common.h src/comm_serie.h config.h

# Dossier des exécutables
BIN_DIR = bin
BIN_TEST_ERROR = $(BIN_DIR)/test_error
BIN_TEST_SERIAL_OPEN = $(BIN_DIR)/test_serial_open

# Mode debug ?
ifeq ($(DEBUG),1)
	CFLAGS += $(DEBUG_FLAGS)
else
	CFLAGS += $(RELEASE_FLAGS)
endif

# Cibles principales
all: $(BIN_TEST_ERROR) $(BIN_TEST_SERIAL_OPEN)

$(BIN_TEST_ERROR): tests/test_error.c $(SRC) $(INCLUDES)
	$(CC) $(CFLAGS) -o $@ $< $(SRC)

$(BIN_TEST_SERIAL_OPEN): tests/test_serial_open.c $(SRC) $(INCLUDES)
	$(CC) $(CFLAGS) -o $@ $< $(SRC)

clean:
	rm -rf $(BIN_DIR)/*

.PHONY: all clean
