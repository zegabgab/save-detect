CC = gcc
SOURCE_DIR = src/
TARGET = target/
TARGET_OBJ = target/obj/
TARGET_BIN = target/bin/
OBJS = $(patsubst $(SOURCE_DIR)%.c, $(TARGET_OBJ)%.o, $(wildcard $(SOURCE_DIR)*.c))

all: dirs main

clean:
	rm -rf $(TARGET)

dirs: $(TARGET) $(TARGET_OBJ) $(TARGET_BIN)

%/:
	mkdir $@

main: $(OBJS)
	$(CC) -o $(TARGET_BIN)stalk $(wildcard $(TARGET_OBJ)*.o)

$(TARGET_OBJ)%.o: $(SOURCE_DIR)%.c
	$(CC) -o $@ -c $?
