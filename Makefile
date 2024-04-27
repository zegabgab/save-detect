CC = gcc
SRC = src
TARGET = target
OBJ = target/obj
BIN = target/bin
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

all: dirs main

clean:
	rm -rf $(TARGET)

dirs: $(TARGET)/ $(OBJ)/ $(BIN)/

%/:
	mkdir $@

main: $(BIN)/stalk

$(BIN)/stalk: $(OBJS)
	$(CC) -o $@ $(OBJ)/*.o

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -o $@ -c $?
