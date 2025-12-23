CC = gcc
CFLAGS = -Wall -Wextra
TARGET = program
SRCS = main.c Queue.c Sort.c File.c 
OBJS = main.o Sort.o Queue.o File.o	
DATA = output.txt result_time.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(DATA)

.PHONY: all clean