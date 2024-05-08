CC = gcc
CFLAGS = -Wall
SRC = src
TARGET = target
OBJ = target/obj
BIN = target/bin
MAIN = stalk
SRCS = $(shell find $(SRC)/ -type f -name '*.c')
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: main

.PHONY: clean
clean:
	rm -rf $(TARGET)

main: $(BIN)/$(MAIN)

$(BIN)/$(MAIN): $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(OBJ)/*.o

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $?
