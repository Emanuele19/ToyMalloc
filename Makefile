
CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = toymalloc.o mem_utils.o main.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGET) $(CFLAGS) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~