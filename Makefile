CC = gcc
SOURCE_DIR = src/
TARGET = target/
TARGET_OBJ = target/obj/
TARGET_BIN = target/obj/
OBJS = $(wildcard $(SOURCE_DIR

all: dirs main

clean:
	rm -rf $(TARGET)

dirs: $(TARGET) $(TARGET_OBJ) $(TARGET_BIN)

%/:
	mkdir $@

main: $(wildcard $(SOURCE_DIR)*.c:.c=.o)
	$(CC) -o $(TARGET_BIN)stalk $(TARGET_OBJ)*.o

%.o: %.c
	$(CC) -o $(TARGET_OBJ)$@ -c $(SOURCE_DIR)$?
