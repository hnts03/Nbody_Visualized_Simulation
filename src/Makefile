
CC = g++
CFLAGS = -c -Wall -std=c++11

SRCS = main.cc nbody.cc
HDEADERS = nbody.h bitmap.h
OBJS = $(SRCS:.cc=.o)
TARGET = nbody

# Default target
all: $(TARGET)
	mv $(TARGET) ..

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# cleanup object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all
