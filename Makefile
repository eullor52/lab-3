CC = gcc
CFLAGS = -Wall -Wextra

TARGET = program

SRCS = main.c File.c Sort.o Queue.c 
OBJS = main.o File.o Sort.o Queue.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

Queue.o: Queue.h
Sort.o: Queue.h Sort.h
File.o: Queue.h Sort.h File.h
main.o: Queue.h Sort.h File.h

.PHONY: all clean