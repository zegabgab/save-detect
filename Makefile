CC = gcc
CFLAGS = -Wall
SRC = src
TARGET = target
OBJ = target/obj
BIN = target/bin
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

all: dirs main

.PHONY: clean
clean:
	rm -rf $(TARGET)

dirs: $(TARGET)/ $(OBJ)/ $(BIN)/

%/:
	mkdir $@

main: $(BIN)/stalk

$(BIN)/stalk: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJ)/*.o

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $?
