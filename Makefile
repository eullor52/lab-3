CC = gcc

CFLAGS = -Wall -Wextra -I./headers

SRC_DIR = sources
OBJ_DIR = objects
INC_DIR = headers

TARGET = program.exe

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

DEP = $(OBJS:.o=.d)
-include $(DEP)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean