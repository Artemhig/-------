CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = console_manager
OBJS = main.o consoles.o

all: $(TARGET)

$(TARGET): $(OBJS)
 $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c consoles.h
 $(CC) $(CFLAGS) -c main.c

consoles.o: consoles.c consoles.h
 $(CC) $(CFLAGS) -c consoles.c

clean:
 rm -f $(OBJS) $(TARGET)

run: $(TARGET)
 ./$(TARGET)

.PHONY: all clean run