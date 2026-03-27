CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = console_manager
OBJS = main.o consoles.o

all: $(TARGET)

$(TARGET): $(OBJS)
 $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp consoles.h
 $(CXX) $(CXXFLAGS) -c main.cpp

consoles.o: consoles.cpp consoles.h
 $(CXX) $(CXXFLAGS) -c consoles.cpp

clean:
 rm -f $(OBJS) $(TARGET)

run: $(TARGET)
 ./$(TARGET)

.PHONY: all clean run